#!/usr/bin/env python3
from pathlib import Path
import argparse,json
ap=argparse.ArgumentParser(description="Compare two ES2 catalogs by canonical path/SHA-256.")
ap.add_argument("old");ap.add_argument("new");ap.add_argument("-o","--out")
a=ap.parse_args()
def load(p):
    x=json.loads(Path(p).read_text(encoding="utf-8"))
    return {r["path"]:r for r in x if isinstance(r,dict) and "path" in r}
old,new=load(a.old),load(a.new)
added=sorted(set(new)-set(old));removed=sorted(set(old)-set(new))
changed=sorted(k for k in set(old)&set(new) if old[k].get("sha256")!=new[k].get("sha256"))
out={"added":added,"removed":removed,"changed":changed,"counts":{"added":len(added),"removed":len(removed),"changed":len(changed)}}
text=json.dumps(out,ensure_ascii=False,indent=2)
if a.out:Path(a.out).write_text(text,encoding="utf-8")
print(text)
