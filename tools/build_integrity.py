#!/usr/bin/env python3
from pathlib import Path
import argparse,hashlib,json
ap=argparse.ArgumentParser();ap.add_argument("root");ap.add_argument("-o","--out",default="INTEGRITY.json");a=ap.parse_args()
root=Path(a.root).resolve();rows=[]
skip={Path(a.out).name}
for p in sorted(root.rglob("*")):
    if not p.is_file() or p.name in skip: continue
    h=hashlib.sha256(p.read_bytes()).hexdigest()
    rows.append({"path":p.relative_to(root).as_posix(),"sha256":h,"bytes":p.stat().st_size})
out={"algorithm":"sha256","files":rows,"count":len(rows)}
(root/a.out).write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding="utf-8")
print(json.dumps({"count":len(rows),"out":str(root/a.out)},ensure_ascii=False))
