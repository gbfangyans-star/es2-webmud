#!/usr/bin/env python3
from pathlib import Path
import argparse,json,collections
ap=argparse.ArgumentParser();ap.add_argument("catalog_dir");a=ap.parse_args();d=Path(a.catalog_dir)
rows=json.loads((d/"all.json").read_text(encoding="utf-8"))
registry={}
for r in rows:
    name=r.get("registered_skill_daemon")
    if name:registry.setdefault(name,[]).append(r["path"])

edges=[];unresolved=[]
def edge(fr,to,kind,detail=None):
    edges.append({"from":fr,"to":to,"kind":kind,**({"detail":detail} if detail else {})})

for r in rows:
    for m in r.get("skill_maps",[]):
        target=m.get("mapped_to")
        hits=registry.get(target,[])
        if len(hits)==1: edge(r["path"],hits[0],"skill_map",{"base":m.get("base"),"name":target})
        else: unresolved.append({"from":r["path"],"kind":"skill_map","name":target,"matches":hits})
    for c in r.get("skill_daemon_calls",[]):
        if c.get("dynamic"):
            unresolved.append({"from":r["path"],"kind":"dynamic_skill_dispatch","expression":c.get("expression"),"method":c.get("method")})
        else:
            hits=registry.get(c.get("skill"),[])
            if len(hits)==1:edge(r["path"],hits[0],"skill_daemon_call",{"method":c.get("method"),"name":c.get("skill")})
            else:unresolved.append({"from":r["path"],"kind":"skill_daemon_call","name":c.get("skill"),"method":c.get("method"),"matches":hits})
    wd=r.get("weapon_dispatch") or {}
    for name in wd.get("wield_as",[]):
        hits=registry.get(name,[])
        if len(hits)==1:edge(r["path"],hits[0],"weapon_wield_skill",{"name":name})
        else:unresolved.append({"from":r["path"],"kind":"weapon_wield_skill","name":name,"matches":hits})
    for name in wd.get("damage_skills",[]):
        hits=registry.get(name,[])
        if len(hits)==1:edge(r["path"],hits[0],"weapon_damage_skill",{"name":name})
        else:unresolved.append({"from":r["path"],"kind":"weapon_damage_skill","name":name,"matches":hits})

incoming=collections.defaultdict(list);outgoing=collections.defaultdict(list)
for e in edges:outgoing[e["from"]].append(e);incoming[e["to"]].append(e)
out={
 "skill_registry":registry,
 "edges":edges,
 "unresolved":unresolved,
 "entities":{r["path"]:{"incoming":incoming.get(r["path"],[]),"outgoing":outgoing.get(r["path"],[])} for r in rows},
 "stats":{"registered_names":len(registry),"edges":len(edges),"unresolved":len(unresolved)}
}
(d/"dependency_graph.json").write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding="utf-8")
print(json.dumps(out["stats"],ensure_ascii=False,indent=2))
