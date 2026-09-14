#!/usr/bin/env python3
"""Transactional canonical-content patch applier.
Dry-run by default. Applies only explicit UTF-8 full-file replacements under source/upstream/mudlib.
Every file requires an expectedBeforeSha256 so stale/concurrent edits are rejected.
"""
from pathlib import Path
import argparse, hashlib, json, os, tempfile, time
ROOT=Path(__file__).resolve().parents[1]
MUD=(ROOT/'source/upstream/mudlib').resolve(); REP=ROOT/'reports'
def sha(b): return hashlib.sha256(b).hexdigest()
def resolve_rel(raw):
    rel=str(raw).replace('\\','/').lstrip('/')
    p=(MUD/rel).resolve()
    try:p.relative_to(MUD)
    except ValueError: raise SystemExit(f'REJECT outside canonical mudlib: {raw}')
    return rel,p
def load_plan(p):
    d=json.loads(Path(p).read_text(encoding='utf-8'))
    if d.get('sourceBoundary')!='taedlar/es2_mudlib only': raise SystemExit('REJECT sourceBoundary mismatch')
    files=d.get('files')
    if not isinstance(files,list) or not files: raise SystemExit('REJECT files must be a non-empty list')
    return d,files
def main():
    ap=argparse.ArgumentParser(); ap.add_argument('plan'); ap.add_argument('--apply',action='store_true'); a=ap.parse_args()
    plan,items=load_plan(a.plan); prepared=[]; seen=set()
    for x in items:
        rel,p=resolve_rel(x.get('path',''))
        if rel in seen: raise SystemExit(f'REJECT duplicate path: {rel}')
        seen.add(rel)
        if not p.is_file(): raise SystemExit(f'REJECT missing canonical file: {rel}')
        before=p.read_bytes(); actual=sha(before); expected=str(x.get('expectedBeforeSha256','')).lower()
        if len(expected)!=64 or actual!=expected: raise SystemExit(f'REJECT stale SHA for {rel}: expected {expected or "<missing>"}, actual {actual}')
        text=x.get('replacementText')
        if not isinstance(text,str): raise SystemExit(f'REJECT replacementText must be string: {rel}')
        after=text.encode('utf-8'); after.decode('utf-8')
        prepared.append((rel,p,before,after,actual,sha(after)))
    result={'ok':True,'applied':False,'dryRun':not a.apply,'version':(ROOT/'VERSION').read_text().strip(),'files':[{'path':r,'beforeSha256':bs,'afterSha256':as_,'changed':bs!=as_} for r,p,b,a,bs,as_ in prepared]}
    if not a.apply:
        print(json.dumps(result,ensure_ascii=False,indent=2)); return
    stamp=time.strftime('%Y%m%d-%H%M%S'); backups=[]; written=[]
    try:
        for rel,p,before,after,bs,as_ in prepared:
            backup=REP/'content_transactions'/stamp/(rel.replace('/','__')+'.bak')
            backup.parent.mkdir(parents=True,exist_ok=True); backup.write_bytes(before); backups.append((rel,backup,bs))
        for rel,p,before,after,bs,as_ in prepared:
            fd,tmp=tempfile.mkstemp(prefix=p.name+'.',suffix='.tmp',dir=p.parent)
            try:
                with os.fdopen(fd,'wb') as f: f.write(after); f.flush(); os.fsync(f.fileno())
                os.replace(tmp,p)
            finally:
                if os.path.exists(tmp): os.unlink(tmp)
            written.append((rel,p,before))
        for rel,p,before,after,bs,as_ in prepared:
            if sha(p.read_bytes())!=as_: raise RuntimeError(f'post-write verification failed: {rel}')
    except Exception:
        for rel,p,before in reversed(written): p.write_bytes(before)
        raise
    manifest={'schema':1,'created':time.strftime('%Y-%m-%dT%H:%M:%S'),'sourceBoundary':'taedlar/es2_mudlib only','plan':str(Path(a.plan)),'files':[{'path':r,'beforeSha256':bs,'afterSha256':as_,'backup':str(bk.relative_to(ROOT))} for (r,p,b,a,bs,as_),(rr,bk,bbs) in zip(prepared,backups)]}
    mf=REP/'content_transactions'/stamp/'manifest.json'; mf.write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding='utf-8')
    result.update({'applied':True,'dryRun':False,'manifest':str(mf.relative_to(ROOT))}); print(json.dumps(result,ensure_ascii=False,indent=2))
if __name__=='__main__': main()
