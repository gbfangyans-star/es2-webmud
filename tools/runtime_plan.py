#!/usr/bin/env python3
from pathlib import Path
import argparse,json,os
ap=argparse.ArgumentParser();ap.add_argument("repo");a=ap.parse_args()
repo=Path(a.repo).resolve()
neo=repo/"neolith"
cands=[]
if neo.exists():
    for p in neo.rglob("*"):
        if not p.is_file(): continue
        n=p.name.lower()
        if n in ("neolith","neolith.exe"):
            cands.append(str(p))
conf=repo/"neolith.conf"
out={
 "repo":str(repo),
 "neolithSubmodule":str(neo),
 "neolithSubmodulePresent":neo.exists(),
 "config":str(conf),
 "configPresent":conf.exists(),
 "binaryCandidates":sorted(cands),
 "autoStartSafe":len(cands)==1 and conf.exists(),
 "canonicalStartShape":"<neolith-binary> -f <repo>/neolith.conf",
 "note":"No binary path is invented. If zero or multiple candidates are found, choose/build Neolith explicitly."
}
print(json.dumps(out,ensure_ascii=False,indent=2))
