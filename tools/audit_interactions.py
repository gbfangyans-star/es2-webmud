#!/usr/bin/env python3
from pathlib import Path
import argparse,json
ap=argparse.ArgumentParser();ap.add_argument("catalog_dir");a=ap.parse_args();d=Path(a.catalog_dir)
rows=json.loads((d/"all.json").read_text(encoding="utf-8"))
issues=[]
for r in rows:
    funcs=set(r.get("functions") or [])
    for a in r.get("actions",[]):
        h=a.get("handler")
        if h and h not in funcs:
            issues.append({"severity":"advisory","kind":"add_action_handler_not_local","path":r["path"],"handler":h,"verb":a.get("verb")})
    for c in r.get("callouts",[]):
        h=c.get("function")
        if h and h not in funcs:
            issues.append({"severity":"advisory","kind":"call_out_handler_not_local","path":r["path"],"handler":h,"delay":c.get("delay")})
out={"count":len(issues),"issues":issues,"note":"Advisory only: handlers may be inherited."}
(d/"interaction_audit.json").write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding="utf-8")
print(json.dumps({"count":len(issues)},ensure_ascii=False))
