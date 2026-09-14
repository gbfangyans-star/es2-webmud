#!/usr/bin/env python3
from pathlib import Path
import argparse,json
ap=argparse.ArgumentParser();ap.add_argument("catalog_dir");a=ap.parse_args();d=Path(a.catalog_dir)
rows=json.loads((d/"all.json").read_text(encoding="utf-8"))
reg={}
for r in rows:
    if r.get("registered_skill_daemon"):reg.setdefault(r["registered_skill_daemon"],[]).append(r["path"])
profiles=[]
for r in rows:
    if r.get("type")!="npc":continue
    mapped=[]
    for m in r.get("skill_maps",[]):
        hits=reg.get(m.get("mapped_to"),[])
        mapped.append({**m,"resolved_path":hits[0] if len(hits)==1 else None,"matches":len(hits)})
    profiles.append({
      "path":r["path"],"name":r.get("name") or r.get("short"),"level":r.get("level"),
      "attributes":r.get("attributes",{}),"stat_maximums":r.get("stat_maximums",{}),
      "skills":r.get("skills",[]),"skill_maps":mapped,"equipment":r.get("equipment",[]),
      "combat_surface":r.get("combat_surface",[]),"damage_contract":r.get("damage_contract",[]),
      "manual_review":r.get("manual_review",[])
    })
(d/"npc_combat_profiles.json").write_text(json.dumps(profiles,ensure_ascii=False,indent=2),encoding="utf-8")
print(json.dumps({"profiles":len(profiles)},ensure_ascii=False))
