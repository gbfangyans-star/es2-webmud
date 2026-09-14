#!/usr/bin/env python3
from pathlib import Path
import argparse,json,difflib,sys
from backup_core import restore_with_safety

ap=argparse.ArgumentParser()
ap.add_argument("root")
sub=ap.add_subparsers(dest="op",required=True)
ls=sub.add_parser("list")
ls.add_argument("--limit",type=int,default=200)
df=sub.add_parser("diff")
df.add_argument("backup")
df.add_argument("current")
rs=sub.add_parser("restore")
rs.add_argument("backup")
rs.add_argument("current")
a=ap.parse_args()

root=Path(a.root).resolve()
patches=(root/"patches").resolve()
upstream=(root/"source/upstream").resolve()

def within(base,p):
    p=Path(p).resolve()
    if p!=base and base not in p.parents:
        raise SystemExit("path rejected")
    return p

if a.op=="list":
    patches.mkdir(parents=True,exist_ok=True)
    rows=[]
    for p in sorted(patches.glob("*.bak"),key=lambda x:x.stat().st_mtime,reverse=True)[:a.limit]:
        rows.append({"name":p.name,"path":str(p.relative_to(root)),"bytes":p.stat().st_size,"mtime":p.stat().st_mtime})
    print(json.dumps(rows,ensure_ascii=False,indent=2))
elif a.op=="diff":
    b=within(patches,root/a.backup)
    c=within(upstream,root/a.current)
    old=b.read_text(encoding="utf-8",errors="replace").splitlines()
    new=c.read_text(encoding="utf-8",errors="replace").splitlines()
    print("\n".join(difflib.unified_diff(old,new,fromfile=str(b.relative_to(root)),tofile=str(c.relative_to(root)),lineterm="")))
elif a.op=="restore":
    try:
        result=restore_with_safety(root,a.backup,a.current)
    except (ValueError,FileNotFoundError) as e:
        raise SystemExit(str(e))
    print(json.dumps(result,ensure_ascii=False))
