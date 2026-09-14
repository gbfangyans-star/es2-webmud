#!/usr/bin/env python3
from pathlib import Path
import argparse,json
ap=argparse.ArgumentParser();ap.add_argument("catalog_dir");a=ap.parse_args();d=Path(a.catalog_dir)
rows=json.loads((d/"all.json").read_text(encoding="utf-8"))
issues=[]
for r in rows:
    sc=r.get("skill_contract") or {}
    funcs=set(sc.get("functions") or [])
    if "attack_using" in funcs and not ("valid_enable" in funcs or r.get("registered_skill_daemon")):
        issues.append({"severity":"advisory","kind":"attack_skill_without_visible_enable_contract","path":r["path"]})
    hooks=set(r.get("equipment_hooks") or [])
    if "wear" in hooks and "remove" not in hooks and r.get("type") in {"item","feature","prototype"}:
        issues.append({"severity":"advisory","kind":"wear_without_visible_remove","path":r["path"]})
    if "wield" in hooks and "unwield" not in hooks and r.get("type") in {"item","feature","prototype"}:
        issues.append({"severity":"advisory","kind":"wield_without_visible_unwield","path":r["path"]})
out={"count":len(issues),"issues":issues,"note":"Advisory source-shape checks only. Inheritance may provide missing contracts."}
(d/"contract_audit.json").write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding="utf-8")
print(json.dumps(out,ensure_ascii=False,indent=2))
