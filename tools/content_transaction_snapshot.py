#!/usr/bin/env python3
"""Create a safe, read-only rollback snapshot manifest for selected canonical paths.
It never edits or restores mudlib files. Paths must resolve inside canonical mudlib.
"""
from pathlib import Path
import argparse,hashlib,json,time,base64
ROOT=Path(__file__).resolve().parents[1]; MUD=(ROOT/'source/upstream/mudlib').resolve(); REP=ROOT/'reports'
def inside(p):
 try:p.resolve().relative_to(MUD); return True
 except ValueError:return False
def main():
 ap=argparse.ArgumentParser(); ap.add_argument('paths',nargs='+'); ap.add_argument('--name',default='content-change'); a=ap.parse_args()
 entries=[]
 for raw in a.paths:
  rel=raw.replace('\\','/').lstrip('/'); p=(MUD/rel).resolve()
  if not inside(p): raise SystemExit(f'REJECT outside canonical mudlib: {raw}')
  if not p.is_file(): raise SystemExit(f'REJECT missing canonical file: {raw}')
  b=p.read_bytes(); entries.append({'path':p.relative_to(MUD).as_posix(),'sha256':hashlib.sha256(b).hexdigest(),'size':len(b),'backupBase64':base64.b64encode(b).decode('ascii')})
 stamp=time.strftime('%Y%m%d-%H%M%S'); safe=''.join(c if c.isalnum() or c in '-_' else '_' for c in a.name)[:60]
 out={'schema':1,'version':(ROOT/'VERSION').read_text().strip(),'created':time.strftime('%Y-%m-%dT%H:%M:%S'),'purpose':'pre-change rollback evidence only','sourceBoundary':'taedlar/es2_mudlib only','autoRestore':False,'files':entries}
 dest=REP/f'content_transaction_{safe}_{stamp}.json'; REP.mkdir(exist_ok=True); dest.write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8')
 print(json.dumps({'ok':True,'files':len(entries),'snapshot':str(dest.relative_to(ROOT)),'autoRestore':False},ensure_ascii=False))
if __name__=='__main__':main()
