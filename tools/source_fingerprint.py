#!/usr/bin/env python3
from pathlib import Path
import argparse,hashlib,json

ap=argparse.ArgumentParser()
ap.add_argument("repo")
ap.add_argument("--out")
a=ap.parse_args()
repo=Path(a.repo).resolve()
mudlib=repo/"mudlib"
if not mudlib.is_dir():
    print(json.dumps({"ok":False,"error":"mudlib missing"},ensure_ascii=False,indent=2))
    raise SystemExit(2)

h=hashlib.sha256()
count=0
total=0
for p in sorted(x for x in mudlib.rglob("*") if x.is_file()):
    rel=p.relative_to(repo).as_posix().encode("utf-8")
    data=p.read_bytes()
    h.update(len(rel).to_bytes(8,"big"));h.update(rel)
    h.update(len(data).to_bytes(8,"big"));h.update(data)
    count+=1;total+=len(data)
out={
    "format":"es2-source-fingerprint-v1",
    "ok":True,
    "scope":"mudlib/**",
    "files":count,
    "bytes":total,
    "treeSha256":h.hexdigest()
}
text=json.dumps(out,ensure_ascii=False,indent=2)
if a.out: Path(a.out).write_text(text,encoding="utf-8")
print(text)
