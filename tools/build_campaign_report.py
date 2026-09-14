#!/usr/bin/env python3
from pathlib import Path
import argparse,json,hashlib,datetime
ap=argparse.ArgumentParser()
ap.add_argument('--release')
ap.add_argument('--runtime-bundle')
ap.add_argument('--session-evidence')
ap.add_argument('--session-chain')
ap.add_argument('--acceptance')
ap.add_argument('--multiplayer')
ap.add_argument('--out',required=True)
a=ap.parse_args()

def load(path):
    if not path:return None
    p=Path(path).resolve()
    if not p.exists():return {'_missing':str(p)}
    data=p.read_bytes()
    try:x=json.loads(data)
    except Exception as e:return {'_invalid':str(e),'file':str(p),'sha256':hashlib.sha256(data).hexdigest()}
    return {'file':p.name,'sha256':hashlib.sha256(data).hexdigest(),'data':x}

items={
 'release':load(a.release),
 'runtime_bundle_manifest':load(str(Path(a.runtime_bundle)/'manifest.json') if a.runtime_bundle else None),
 'session_evidence':load(a.session_evidence),
 'session_chain':load(a.session_chain),
 'acceptance':load(a.acceptance),
 'multiplayer':load(a.multiplayer)
}
checks={}
checks['release']=bool(items['release'] and items['release'].get('data',{}).get('ok'))
rb=items['runtime_bundle_manifest'];checks['runtime_bundle']=bool(rb and rb.get('data',{}).get('complete'))
se=items['session_evidence'];checks['session_evidence']=bool(se and se.get('data',{}).get('records',0)>0)
sc=items['session_chain'];checks['session_chain']=bool(sc and sc.get('data',{}).get('records',0)>0)
ac=items['acceptance'];checks['acceptance']=bool(ac and ac.get('data',{}).get('complete'))
mp=items['multiplayer'];checks['multiplayer']=bool(mp and all(s.get('status')=='pass' for s in mp.get('data',{}).get('stages',[])) and len(mp.get('data',{}).get('stages',[]))>=9)
missing=[k for k,v in checks.items() if not v]
out={
 'format':'es2-validation-campaign-v1',
 'generatedAt':datetime.datetime.now(datetime.timezone.utc).isoformat(),
 'checks':checks,
 'complete':not missing,
 'missingOrIncomplete':missing,
 'artifacts':items,
 'note':'Campaign aggregation only. Each underlying validator remains authoritative for its own artifact.'
}
Path(a.out).write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({'ok':True,'complete':out['complete'],'missingOrIncomplete':missing,'out':a.out},ensure_ascii=False,indent=2))
