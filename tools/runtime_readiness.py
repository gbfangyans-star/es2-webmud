#!/usr/bin/env python3
from pathlib import Path
import argparse,json,subprocess,socket
ap=argparse.ArgumentParser()
ap.add_argument("repo")
ap.add_argument("--host",default="127.0.0.1")
ap.add_argument("--port",type=int,default=4000)
a=ap.parse_args()
repo=Path(a.repo).resolve()

checks={}
checks["mudlib_char"]=(repo/"mudlib/std/char.c").exists()
checks["neolith_conf"]=(repo/"neolith.conf").exists()
checks["neolith_submodule_path"]=(repo/"neolith").exists()
try:
    s=socket.create_connection((a.host,a.port),timeout=0.5);s.close();checks["mud_port_open"]=True
except Exception:
    checks["mud_port_open"]=False
out={"ready_for_browser_runtime":all(checks.values()),"checks":checks,"mud_host":a.host,"mud_port":a.port}
print(json.dumps(out,ensure_ascii=False,indent=2))
