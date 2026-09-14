#!/usr/bin/env python3
from pathlib import Path
import argparse,subprocess,json,socket,shutil,sys
ap=argparse.ArgumentParser(); ap.add_argument("repo"); ap.add_argument("--host",default="127.0.0.1"); ap.add_argument("--port",type=int,default=4000); a=ap.parse_args()
repo=Path(a.repo).resolve(); here=Path(__file__).resolve().parent
def run(cmd):
 p=subprocess.run(cmd,capture_output=True,text=True,timeout=4)
 try:r=json.loads(p.stdout)
 except:r={"stdout":p.stdout,"stderr":p.stderr}
 return {"ok":p.returncode==0,"result":r}
checks={}
checks["source"]=run([sys.executable,str(here/"verify_source.py"),str(repo)])
checks["python"]={"ok":True,"result":sys.version.split()[0]}
checks["node"]={"ok":shutil.which("node") is not None,"result":shutil.which("node")}
checks["npm"]={"ok":shutil.which("npm") is not None,"result":shutil.which("npm")}
checks["neolith_path"]={"ok":(repo/"neolith").exists(),"result":str(repo/"neolith")}
checks["neolith_conf"]={"ok":(repo/"neolith.conf").exists(),"result":str(repo/"neolith.conf")}
try:
 s=socket.create_connection((a.host,a.port),timeout=.25); s.close(); online=True
except: online=False
checks["mud_port"]={"ok":online,"result":f"{a.host}:{a.port}"}
critical=["source","python","node","npm","neolith_path","neolith_conf"]
out={"ok":all(checks[k]["ok"] for k in critical),"runtime_online":online,"checks":checks,
"next":"Start Neolith, then run runtime smoke and browser acceptance capture."}
print(json.dumps(out,ensure_ascii=False,indent=2))
raise SystemExit(0 if out["ok"] else 2)
