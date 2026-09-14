#!/usr/bin/env python3
from pathlib import Path
import argparse,json,hashlib
from campaign_binding import binding_from_campaign

ap=argparse.ArgumentParser()
ap.add_argument("--campaign",required=True)
ap.add_argument("--release",required=True)
ap.add_argument("--runtime-bundle",required=True)
ap.add_argument("--session-package",required=True)
ap.add_argument("--multiplayer",required=True)
a=ap.parse_args()
expected=binding_from_campaign(a.campaign)
issues=[]

def load(label,path):
    try:return json.loads(Path(path).read_text(encoding="utf-8"))
    except Exception as e:
        issues.append({"kind":"artifact_invalid","artifact":label,"error":str(e)});return {}

artifacts={
 "release":load("release",a.release),
 "runtime":load("runtime",Path(a.runtime_bundle)/"manifest.json"),
 "session":load("session",Path(a.session_package)/"manifest.json"),
 "multiplayer":load("multiplayer",a.multiplayer)
}
keys=["campaignId","campaignSha256","projectVersion","sourceCommit","mudlibTreeSha256"]
for label,obj in artifacts.items():
    b=obj.get("campaignBinding")
    if not isinstance(b,dict):
        issues.append({"kind":"campaign_binding_missing","artifact":label});continue
    for k in keys:
        if b.get(k)!=expected.get(k):
            issues.append({"kind":"campaign_binding_mismatch","artifact":label,"field":k,"expected":expected.get(k),"actual":b.get(k)})
out={"ok":not issues,"campaignId":expected["campaignId"],"expected":expected,"issues":issues}
print(json.dumps(out,ensure_ascii=False,indent=2))
raise SystemExit(0 if out["ok"] else 2)
