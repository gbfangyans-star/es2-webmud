#!/usr/bin/env python3
"""Create/compare a canonical content fingerprint without modifying gameplay."""
from pathlib import Path
import argparse, hashlib, json, time
ROOT=Path(__file__).resolve().parents[1]
MUD=ROOT/'source/upstream/mudlib'
DEFAULT=ROOT/'reports/content_source_baseline.json'
APPROVED=ROOT/'reports/approved_custom_extensions.json'

def scan():
    files={}
    for p in sorted(MUD.rglob('*')):
        if p.is_file():
            rel=p.relative_to(MUD).as_posix()
            files[rel]=hashlib.sha256(p.read_bytes()).hexdigest()
    return files

def main():
    ap=argparse.ArgumentParser(); ap.add_argument('--baseline',default=str(DEFAULT)); ap.add_argument('--write-baseline',action='store_true'); a=ap.parse_args()
    bp=Path(a.baseline); now=scan()
    if a.write_baseline or not bp.exists():
        out={'schema':1,'sourceBoundary':'taedlar/es2_mudlib only','created':time.strftime('%Y-%m-%dT%H:%M:%S'),'files':now}
        bp.parent.mkdir(parents=True,exist_ok=True); bp.write_text(json.dumps(out,indent=2,ensure_ascii=False),encoding='utf-8')
        print(json.dumps({'ok':True,'mode':'baseline','files':len(now),'path':str(bp.relative_to(ROOT))},ensure_ascii=False)); return 0
    old=json.loads(bp.read_text(encoding='utf-8')).get('files',{})
    approved={}
    if APPROVED.exists():
        approved=json.loads(APPROVED.read_text(encoding='utf-8')).get('files',{})
    raw_added=sorted(set(now)-set(old)); raw_removed=sorted(set(old)-set(now)); raw_changed=sorted(k for k in set(now)&set(old) if now[k]!=old[k])
    is_approved=lambda k: k in approved and now.get(k)==approved[k]
    approved_custom=sorted(k for k in raw_added+raw_changed if is_approved(k))
    added=sorted(k for k in raw_added if not is_approved(k)); removed=raw_removed; changed=sorted(k for k in raw_changed if not is_approved(k))
    out={'ok':not(added or removed or changed),'mode':'compare','files':len(now),'added':added,'removed':removed,'changed':changed,'approvedCustom':approved_custom,'counts':{'added':len(added),'removed':len(removed),'changed':len(changed)}}
    (ROOT/'reports/content_source_change.json').write_text(json.dumps(out,indent=2,ensure_ascii=False),encoding='utf-8')
    print(json.dumps(out,ensure_ascii=False)); return 0 if out['ok'] else 2
if __name__=='__main__': raise SystemExit(main())
