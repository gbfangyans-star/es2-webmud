#!/usr/bin/env python3
from pathlib import Path
import argparse,subprocess,sys,json

ap=argparse.ArgumentParser()
ap.add_argument("repo")
ap.add_argument("--host",default="127.0.0.1")
ap.add_argument("--port",type=int,default=4000)
a=ap.parse_args()
here=Path(__file__).resolve().parent

def run(args):
    p=subprocess.run(args,capture_output=True,text=True)
    try: payload=json.loads(p.stdout) if p.stdout.strip() else {}
    except Exception: payload={"stdout":p.stdout,"stderr":p.stderr}
    return {"ok":p.returncode==0,"code":p.returncode,"result":payload}

verify=run([sys.executable,str(here/"verify_source.py"),a.repo])
probe=run([sys.executable,str(here/"runtime_probe.py"),"--host",a.host,"--port",str(a.port)])
out={
  "ok":verify["ok"] and probe["ok"],
  "source":verify,
  "tcp_probe":probe,
  "next_checks":[
    "capture canonical login transcript",
    "validate existing-login or new-character prompts",
    "perform human-reviewed movement/look/score/skills/inventory smoke test"
  ]
}
print(json.dumps(out,ensure_ascii=False,indent=2))
raise SystemExit(0 if out["ok"] else 2)
