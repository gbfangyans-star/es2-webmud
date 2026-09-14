#!/usr/bin/env python3
from pathlib import Path
import argparse,json,subprocess
ap=argparse.ArgumentParser();ap.add_argument("mudlib_root");ap.add_argument("catalog_dir");a=ap.parse_args();root=Path(a.mudlib_root).resolve();d=Path(a.catalog_dir)
def git(*args):
    try:return subprocess.check_output(["git","-C",str(root),*args],text=True,stderr=subprocess.DEVNULL).strip()
    except:return None
origin=git("remote","get-url","origin");branch=git("rev-parse","--abbrev-ref","HEAD");commit=git("rev-parse","HEAD");status=git("status","--porcelain");dirty=None if status is None else bool(status)
allrows=json.loads((d/"all.json").read_text(encoding="utf-8")) if (d/"all.json").exists() else [];audit=json.loads((d/"audit.json").read_text(encoding="utf-8")) if (d/"audit.json").exists() else {};core=json.loads((d/"core_audit.json").read_text(encoding="utf-8")) if (d/"core_audit.json").exists() else {}
out={"expected_origin":"https://github.com/taedlar/es2_mudlib","origin":origin,"origin_verified":bool(origin and "github.com/taedlar/es2_mudlib" in origin),"branch":branch,"commit":commit,"dirty":dirty,"catalog_files":len(allrows),"audit_stats":audit.get("stats",{}),"core_ok":core.get("ok"),"source_policy":"taedlar/es2_mudlib only"}
(d/"source_status.json").write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding="utf-8");print(json.dumps(out,ensure_ascii=False))
