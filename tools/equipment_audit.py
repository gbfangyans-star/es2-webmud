#!/usr/bin/env python3
from pathlib import Path
import argparse,json,collections,sys
ap=argparse.ArgumentParser(description="Audit source-derived ES2 equipment metadata.")
ap.add_argument("catalog_dir");a=ap.parse_args();d=Path(a.catalog_dir)
rows=json.loads((d/"equipment_index.json").read_text(encoding="utf-8"))
issues=[]
for r in rows:
    if r.get("armor_apply") and not r.get("wear_as"):
        issues.append({"kind":"armor_without_wear_as","path":r["path"]})
    for apv in r.get("armor_apply",[]):
        if r.get("wear_as") and apv.get("slot")!=r.get("wear_as"):
            issues.append({"kind":"armor_slot_mismatch","path":r["path"],"wear_as":r.get("wear_as"),"apply_slot":apv.get("slot")})
summary={"equipment":len(rows),"issues":len(issues),"issue_counts":dict(collections.Counter(x["kind"] for x in issues))}
out={"summary":summary,"issues":issues,"source_policy":"taedlar/es2_mudlib only"}
(d/"equipment_audit.json").write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding="utf-8")
print(json.dumps(out,ensure_ascii=False,indent=2))
sys.exit(2 if issues else 0)
