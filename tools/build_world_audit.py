#!/usr/bin/env python3
from pathlib import Path
import argparse,json,collections,posixpath
ap=argparse.ArgumentParser();ap.add_argument("catalog_dir");a=ap.parse_args();d=Path(a.catalog_dir)
rows=json.loads((d/"all.json").read_text(encoding="utf-8"));by={r["path"]:r for r in rows}
def domain_of(path):
    if path.startswith("/d/"):
        parts=path.split("/");return parts[2] if len(parts)>2 else ""
    return "(core)"
domains=collections.defaultdict(lambda:collections.Counter());manual=collections.defaultdict(list);interactive=collections.defaultdict(int)
for r in rows:
    dom=domain_of(r["path"]);domains[dom][r.get("type","unknown")]+=1
    if r.get("manual_review"):manual[dom].append(r["path"])
    interactive[dom]+=len(r.get("actions",[]))+len(r.get("callouts",[]))+len(r.get("doors",[]))+len(r.get("accept_hooks",[]))
domain_rows=[]
for dom in sorted(domains):
    c=domains[dom];domain_rows.append({"domain":dom,"total":sum(c.values()),"counts":dict(sorted(c.items())),"manual_review":len(manual[dom]),"interactive_hooks":interactive[dom]})
object_refs=collections.Counter();skill_refs=collections.Counter()
for r in rows:
    for key in ("objects","merchandise"):
        for x in r.get(key,[]):
            t=x.get("target");rel=x.get("relative",False)
            if t:
                if rel:t=posixpath.normpath(posixpath.join(posixpath.dirname(r["path"]),t))
                object_refs[t]+=1
    for x in r.get("equipment",[]):
        t=x.get("target")
        if t:object_refs[t]+=1
    for m in r.get("skill_maps",[]):
        if m.get("mapped_to"):skill_refs[m["mapped_to"]]+=1
orphans={"npc":[],"item":[],"skill":[]}
for r in rows:
    typ=r.get("type")
    if typ in ("npc","item") and object_refs[r["path"]]==0:orphans[typ].append(r["path"])
    if typ=="skill":
        name=r.get("registered_skill_daemon")
        if name and skill_refs[name]==0:orphans["skill"].append(r["path"])
hotspots=[]
for r in rows:
    score=len(r.get("actions",[]))+len(r.get("callouts",[]))+len(r.get("doors",[]))+len(r.get("accept_hooks",[]))
    if score:hotspots.append({"path":r["path"],"type":r.get("type"),"name":r.get("name") or r.get("short"),"score":score,"actions":len(r.get("actions",[])),"callouts":len(r.get("callouts",[])),"doors":len(r.get("doors",[])),"accept_hooks":len(r.get("accept_hooks",[])),"manual_review":bool(r.get("manual_review"))})
hotspots.sort(key=lambda x:(-x["score"],x["path"]))
out={"domains":domain_rows,"orphans":orphans,"interaction_hotspots":hotspots[:500],"stats":{"domains":len(domain_rows),"orphan_npcs":len(orphans["npc"]),"orphan_items":len(orphans["item"]),"orphan_skills":len(orphans["skill"]),"interactive_entities":len(hotspots)},"note":"Orphan results are structural hints only. Dynamic clone/load/inheritance references may not be statically visible."}
(d/"world_audit.json").write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding="utf-8");print(json.dumps(out["stats"],ensure_ascii=False))
