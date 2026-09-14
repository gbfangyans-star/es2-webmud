#!/usr/bin/env python3
from pathlib import Path
import argparse,json,collections
ap=argparse.ArgumentParser();ap.add_argument("catalog_dir");a=ap.parse_args();d=Path(a.catalog_dir)
rows=json.loads((d/"all.json").read_text(encoding="utf-8"));dep=json.loads((d/"dependency_graph.json").read_text(encoding="utf-8")) if (d/"dependency_graph.json").exists() else {"unresolved":[]};audit=json.loads((d/"audit.json").read_text(encoding="utf-8")) if (d/"audit.json").exists() else {"issues":[]}
score=collections.Counter();why=collections.defaultdict(list)
for r in rows:
    p=r["path"]
    if r.get("manual_review"):
        n=max(1,len(r["manual_review"]));score[p]+=3*n;why[p].append({"kind":"manual_review","count":n})
    if r.get("actions"):score[p]+=len(r["actions"]);why[p].append({"kind":"actions","count":len(r["actions"])})
    if r.get("callouts"):score[p]+=2*len(r["callouts"]);why[p].append({"kind":"callouts","count":len(r["callouts"])})
    if r.get("accept_hooks"):score[p]+=2*len(r["accept_hooks"]);why[p].append({"kind":"accept_hooks","count":len(r["accept_hooks"])})
for u in dep.get("unresolved",[]):
    p=u.get("from");score[p]+=4;why[p].append({"kind":"unresolved_dependency","detail":u})
for i in audit.get("issues",[]):
    p="/"+i.get("file","").removesuffix(".c");score[p]+=5;why[p].append({"kind":"audit_issue","detail":i})
ranked=[{"path":p,"score":s,"reasons":why[p]} for p,s in score.most_common()];out={"ranked":ranked,"stats":{"entities":len(ranked),"max_score":ranked[0]["score"] if ranked else 0}}
(d/"triage.json").write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding="utf-8");print(json.dumps(out["stats"],ensure_ascii=False))
