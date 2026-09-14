#!/usr/bin/env python3
from pathlib import Path
import argparse,subprocess,sys,json,hashlib,uuid,datetime

ap=argparse.ArgumentParser()
ap.add_argument("--root",required=True)
ap.add_argument("--repo",required=True)
ap.add_argument("--out",required=True)
a=ap.parse_args()
root=Path(a.root).resolve()
repo=Path(a.repo).resolve()
out=Path(a.out).resolve()
here=Path(__file__).resolve().parent

def run_json(cmd):
    p=subprocess.run(cmd,capture_output=True,text=True)
    try:x=json.loads(p.stdout)
    except Exception:x={"stdout":p.stdout,"stderr":p.stderr}
    if p.returncode!=0:return False,x
    return True,x

ok_source,source=run_json([sys.executable,str(here/"verify_source.py"),str(repo)])
if not ok_source or not source.get("ok"):
    print(json.dumps({"ok":False,"stage":"verify_source","result":source},ensure_ascii=False,indent=2))
    raise SystemExit(2)
ok_fp,fp=run_json([sys.executable,str(here/"source_fingerprint.py"),str(repo)])
if not ok_fp or not fp.get("ok"):
    print(json.dumps({"ok":False,"stage":"source_fingerprint","result":fp},ensure_ascii=False,indent=2))
    raise SystemExit(2)

version=(root/"VERSION").read_text(encoding="utf-8").strip()
payload={
    "format":"es2-validation-campaign-v1",
    "campaignId":str(uuid.uuid4()),
    "createdUtc":datetime.datetime.now(datetime.timezone.utc).isoformat(),
    "projectVersion":version,
    "source":{
        "origin":source.get("origin"),
        "branch":source.get("branch"),
        "commit":source.get("commit"),
        "dirty":source.get("dirty"),
        "mudlibTreeSha256":fp.get("treeSha256"),
        "files":fp.get("files"),
        "bytes":fp.get("bytes")
    },
    "rule":"All release/runtime/session/multiplayer evidence in one final campaign must bind to this exact campaign manifest, source commit, and mudlib tree fingerprint."
}
out.parent.mkdir(parents=True,exist_ok=True)
text=json.dumps(payload,ensure_ascii=False,indent=2)
out.write_text(text,encoding="utf-8")
sha=hashlib.sha256(out.read_bytes()).hexdigest()
print(json.dumps({"ok":True,"campaignId":payload["campaignId"],"campaignSha256":sha,"mudlibTreeSha256":fp.get("treeSha256"),"out":str(out)},ensure_ascii=False,indent=2))
