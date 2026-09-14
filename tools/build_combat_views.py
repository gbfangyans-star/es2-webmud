#!/usr/bin/env python3
from pathlib import Path
import argparse,json,collections
ap=argparse.ArgumentParser(description="Build source-derived combat/equipment views.")
ap.add_argument("catalog_dir");a=ap.parse_args();d=Path(a.catalog_dir)
rows=json.loads((d/"all.json").read_text(encoding="utf-8"))

equipment=[]
for r in rows:
    if r.get("type")!="item": continue
    if r.get("wear_as") or r.get("armor_apply") or r.get("weapon_type") or any("ARMOR" in x or "WEAPON" in x for x in r.get("inherits",[])):
        equipment.append({
          "path":r["path"],"name":r.get("name") or r.get("short"),"ids":r.get("ids",[]),
          "wear_as":r.get("wear_as"),"armor_apply":r.get("armor_apply",[]),
          "weapon_type":r.get("weapon_type"),"damage":r.get("damage"),"armor":r.get("armor"),
          "value":r.get("value"),"weight":r.get("weight"),"material":r.get("material"),
          "setup_kinds":r.get("setup_kinds",[]),"apply_mappings":r.get("apply_mappings",[]),
          "inherits":r.get("inherits",[]),"manual_review":r.get("manual_review",[])
        })

combat_npcs=[]
for r in rows:
    if r.get("type")!="npc": continue
    if r.get("skills") or r.get("equipment") or "combat" in r.get("combat_surface",[]) or r.get("level") is not None:
        combat_npcs.append({
          "path":r["path"],"name":r.get("name") or r.get("short"),"level":r.get("level"),
          "race":r.get("race"),"class":r.get("class"),"attributes":r.get("attributes",{}),
          "stat_maximums":r.get("stat_maximums",{}),"skills":r.get("skills",[]),
          "skill_maps":r.get("skill_maps",[]),"equipment":r.get("equipment",[]),
          "combat_surface":r.get("combat_surface",[]),"manual_review":r.get("manual_review",[])
        })

core=[]
for r in rows:
    if r.get("combat_surface"):
        core.append({"path":r["path"],"type":r.get("type"),"functions":r.get("functions",[]),
                     "combat_surface":r.get("combat_surface",[]),"inherits":r.get("inherits",[])})

slots=collections.Counter(x.get("wear_as") or "(unspecified)" for x in equipment)
summary={"equipment":len(equipment),"combat_npcs":len(combat_npcs),"combat_core_files":len(core),
         "wear_slots":dict(slots)}
for fn,obj in [("equipment_index.json",equipment),("combat_npc_index.json",combat_npcs),
               ("combat_core_index.json",core),("combat_summary.json",summary)]:
    (d/fn).write_text(json.dumps(obj,ensure_ascii=False,indent=2),encoding="utf-8")
print(json.dumps(summary,ensure_ascii=False,indent=2))
