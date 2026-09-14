#!/usr/bin/env python3
from pathlib import Path
import argparse,json
from campaign_binding import binding_from_campaign
ap=argparse.ArgumentParser()
ap.add_argument("--campaign",required=True)
ap.add_argument("--release",required=True)
ap.add_argument("--out",required=True)
a=ap.parse_args()
release=json.loads(Path(a.release).read_text(encoding="utf-8"))
release["campaignBinding"]=binding_from_campaign(a.campaign)
Path(a.out).write_text(json.dumps(release,ensure_ascii=False,indent=2),encoding="utf-8")
print(json.dumps({"ok":True,"out":a.out,"campaignId":release["campaignBinding"]["campaignId"]},ensure_ascii=False))
