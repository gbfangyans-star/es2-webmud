#!/usr/bin/env python3
"""Two-phase restart persistence snapshot. It never edits gameplay data.
BEFORE records canonical save-file hashes/sizes for two existing players after the operator has saved them.
AFTER verifies those files survived a Neolith restart and emits a comparison report.
"""
import argparse,hashlib,json,time
from pathlib import Path

def sha(p): return hashlib.sha256(p.read_bytes()).hexdigest()
def version(root):
 p=root/'VERSION'
 return p.read_text(encoding='utf-8').strip() if p.exists() else 'unknown'
def paths(mud,u): return [mud/'data/user'/u[0]/(u+'.o'),mud/'data/login'/u[0]/(u+'.o')]
def snap(mud,users):
 out={}
 for u in users:
  out[u]=[]
  for p in paths(mud,u):
   out[u].append({'path':str(p.relative_to(mud)),'exists':p.exists(),'bytes':p.stat().st_size if p.exists() else 0,'sha256':sha(p) if p.exists() and p.stat().st_size else None})
 return out

def main():
 ap=argparse.ArgumentParser();ap.add_argument('phase',choices=['before','after']);ap.add_argument('--root',default=str(Path(__file__).resolve().parents[1]));ap.add_argument('--user-a');ap.add_argument('--user-b');ap.add_argument('--state',default='restart_recovery_before.json');ap.add_argument('--report',default='restart_recovery_report.json');a=ap.parse_args()
 root=Path(a.root);mud=root/'source/upstream/mudlib';ua=(a.user_a or input('Existing user A: ')).strip().lower();ub=(a.user_b or input('Existing user B: ')).strip().lower()
 if not ua or not ub or ua==ub: print('Need two different existing ids.');return 2
 users=[ua,ub]; now=snap(mud,users)
 if a.phase=='before':
  missing=[x['path'] for rows in now.values() for x in rows if not x['exists'] or x['bytes']<=0]
  data={'version':version(root),'created':time.strftime('%Y-%m-%dT%H:%M:%S'),'users':users,'files':now,'ok':not missing,'missing':missing}
  Path(a.state).write_text(json.dumps(data,ensure_ascii=False,indent=2),encoding='utf-8');print(json.dumps(data,ensure_ascii=False,indent=2));print('\nState:',a.state);return 0 if data['ok'] else 3
 before=json.loads(Path(a.state).read_text(encoding='utf-8'))
 if before.get('users')!=users: print('Users do not match BEFORE snapshot.');return 3
 changed=[];missing=[]
 for u in users:
  b={x['path']:x for x in before['files'][u]}; n={x['path']:x for x in now[u]}
  for p,x in n.items():
   if not x['exists'] or x['bytes']<=0: missing.append(p)
   elif p in b and (b[p]['sha256']!=x['sha256'] or b[p]['bytes']!=x['bytes']): changed.append({'path':p,'before':b[p],'after':x})
 tmp=[str(p.relative_to(mud)) for base in ('data/user','data/login') for u in users for p in (mud/base/u[0]).glob(u+'.o.tmp*') if (mud/base/u[0]).exists()]
 rep={'version':version(root),'checked':time.strftime('%Y-%m-%dT%H:%M:%S'),'users':users,'beforeCreated':before.get('created'),'filesAfter':now,'missing':missing,'changedAcrossRestart':changed,'orphanTmp':tmp,'ok':not missing and not changed and not tmp}
 Path(a.report).write_text(json.dumps(rep,ensure_ascii=False,indent=2),encoding='utf-8');print(json.dumps(rep,ensure_ascii=False,indent=2));print('\nReport:',a.report);return 0 if rep['ok'] else 3
if __name__=='__main__': raise SystemExit(main())
