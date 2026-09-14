#!/usr/bin/env python3
from pathlib import Path
import argparse,subprocess,sys,json,re

ap=argparse.ArgumentParser()
ap.add_argument("repo")
a=ap.parse_args()
repo=Path(a.repo).resolve()

markers=[
    "mudlib/std/char.c",
    "mudlib/feature/char/combat.c",
    "mudlib/feature/char/attack.c",
    "mudlib/adm/daemons/combatd.c",
    "mudlib/d/snow",
]
missing=[x for x in markers if not (repo/x).exists()]

def git(*args):
    try:
        return subprocess.check_output(["git","-C",str(repo),*args],text=True,stderr=subprocess.DEVNULL).strip()
    except Exception:
        return ""

origin=git("remote","get-url","origin")
branch=git("rev-parse","--abbrev-ref","HEAD")
commit=git("rev-parse","HEAD")
dirty=bool(git("status","--porcelain")) if (repo/".git").exists() else None

def canonical_origin(x):
    if not x:
        return False
    x=x.strip().rstrip("/")
    x=re.sub(r"\.git$","",x)
    allowed={
        "https://github.com/taedlar/es2_mudlib",
        "git@github.com:taedlar/es2_mudlib",
        "ssh://git@github.com/taedlar/es2_mudlib",
    }
    return x in allowed

ok=(not missing) and canonical_origin(origin)
out={
    "ok":ok,
    "repo":str(repo),
    "origin":origin,
    "origin_verified":canonical_origin(origin),
    "branch":branch,
    "commit":commit,
    "dirty":dirty,
    "missing":missing,
    "expected":"https://github.com/taedlar/es2_mudlib"
}
print(json.dumps(out,ensure_ascii=False,indent=2))
sys.exit(0 if ok else 2)
