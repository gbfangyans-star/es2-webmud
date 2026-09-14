#!/usr/bin/env python3
"""Read-only impact analysis for canonical mudlib changes against the sealed baseline."""
from pathlib import Path
import hashlib,json,time
ROOT=Path(__file__).resolve().parents[1]; MUD=ROOT/'source/upstream/mudlib'; REP=ROOT/'reports'; BASE=REP/'content_source_baseline.json'; CAT=ROOT/'catalog/generated'; APPROVED=REP/'approved_custom_extensions.json'
def sha(p): return hashlib.sha256(p.read_bytes()).hexdigest()
def scan(): return {p.relative_to(MUD).as_posix():sha(p) for p in sorted(MUD.rglob('*')) if p.is_file()}
def load(p,d):
 try:return json.loads(p.read_text(encoding='utf-8'))
 except Exception:return d
old=load(BASE,{}).get('files',{}); now=scan()
raw_added=sorted(set(now)-set(old)); removed=sorted(set(old)-set(now)); raw_changed=sorted(k for k in set(now)&set(old) if now[k]!=old[k])
approved=load(APPROVED,{}).get('files',{})
is_approved=lambda k: k in approved and now.get(k)==approved[k]
approved_custom=sorted(k for k in raw_added+raw_changed if is_approved(k))
added=sorted(k for k in raw_added if not is_approved(k)); changed=sorted(k for k in raw_changed if not is_approved(k)); touched=set(added+removed+changed)
rows=load(CAT/'all.json',[])
imp=[]
for r in rows:
 path=str(r.get('path','')).lstrip('/')
 if path in touched or any(path.endswith('/'+x) for x in touched):
  imp.append({'id':r.get('id'),'type':r.get('type'),'name':r.get('name'),'path':r.get('path'),'manual_review':bool(r.get('manual_review'))})
out={'schema':1,'version':(ROOT/'VERSION').read_text().strip(),'generated':time.strftime('%Y-%m-%dT%H:%M:%S'),'readOnly':True,'baseline':str(BASE.relative_to(ROOT)),'sourceBoundary':'taedlar/es2_mudlib only','changes':{'added':added,'removed':removed,'changed':changed},'approvedCustom':approved_custom,'counts':{'added':len(added),'removed':len(removed),'changed':len(changed),'catalogEntitiesDirectlyImpacted':len(imp)},'directCatalogImpact':imp,'requiresReview':bool(touched),'note':'This report never applies or reverts gameplay changes.'}
REP.mkdir(exist_ok=True); (REP/'content_change_impact.json').write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({'ok':True,'changedFiles':len(touched),'catalogEntitiesDirectlyImpacted':len(imp),'output':'reports/content_change_impact.json'},ensure_ascii=False))
