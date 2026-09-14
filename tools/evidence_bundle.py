#!/usr/bin/env python3
from pathlib import Path
import argparse,json,hashlib,datetime,sys
from campaign_binding import binding_from_campaign

ap=argparse.ArgumentParser(description="Build a local runtime-validation evidence bundle.")
ap.add_argument("out_dir")
ap.add_argument("--campaign",required=True)
ap.add_argument("--source-status")
ap.add_argument("--runtime-smoke")
ap.add_argument("--login-transcript")
ap.add_argument("--movement-transcript")
ap.add_argument("--combat-transcript")
ap.add_argument("--reconnect-transcript")
a=ap.parse_args()

out=Path(a.out_dir).resolve()
out.mkdir(parents=True,exist_ok=True)
binding=binding_from_campaign(a.campaign)
files={}
for key,val in vars(a).items():
    if key in ("out_dir","campaign") or not val: continue
    p=Path(val).resolve()
    if not p.exists(): raise SystemExit(f"missing evidence file: {p}")
    data=p.read_bytes()
    dst=out/p.name
    dst.write_bytes(data)
    files[key]={
      "file":dst.name,
      "sha256":hashlib.sha256(data).hexdigest(),
      "bytes":len(data)
    }

required=["source_status","runtime_smoke","login_transcript","movement_transcript","combat_transcript","reconnect_transcript"]
manifest={
  "format":"es2-runtime-evidence-v2",
  "created_utc":datetime.datetime.now(datetime.timezone.utc).isoformat(),
  "campaignBinding":binding,
  "required":required,
  "present":files,
  "complete":all(k in files for k in required),
  "note":"Evidence bundle records observed runtime artifacts only. It does not alter or simulate ES2 gameplay."
}
(out/"manifest.json").write_text(json.dumps(manifest,ensure_ascii=False,indent=2),encoding="utf-8")
print(json.dumps(manifest,ensure_ascii=False,indent=2))
raise SystemExit(0 if manifest["complete"] else 3)
