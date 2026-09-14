#!/usr/bin/env python3
from pathlib import Path
import argparse,json,re

ap=argparse.ArgumentParser()
ap.add_argument("root")
a=ap.parse_args()
root=Path(a.root).resolve()

issues=[]
ps1=list(root.rglob("*.ps1"))
for p in ps1:
    data=p.read_bytes()
    rel=p.relative_to(root).as_posix()
    # PowerShell 5.1 safely handles ASCII or UTF-8 BOM here.
    ascii_only=all(b < 128 for b in data)
    has_bom=data.startswith(b"\xef\xbb\xbf")
    if not (ascii_only or has_bom):
        issues.append({"kind":"encoding_not_ps51_safe","file":rel})
    text=data.decode("utf-8-sig",errors="replace")
    if re.search(r'(?<![\w.])npm\s+(?:install|start)\b',text):
        issues.append({"kind":"plain_npm_ps1_risk","file":rel})
    if "\ufffd" in text:
        issues.append({"kind":"decode_replacement","file":rel})

required=["source/fetch_es2.ps1","setup_windows.ps1","runtime_windows.ps1"]
for rel in required:
    if not (root/rel).exists():
        issues.append({"kind":"required_missing","file":rel})

out={"ok":not issues,"scripts":len(ps1),"issues":issues}
print(json.dumps(out,ensure_ascii=False,indent=2))
raise SystemExit(0 if out["ok"] else 2)
