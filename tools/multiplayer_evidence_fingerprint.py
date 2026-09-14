#!/usr/bin/env python3
"""Build gate-scoped fingerprints for multiplayer live evidence freshness.

The goal is conservative reuse of *human-run* Windows/Neolith evidence. A live
PASS remains fresh only while the source/bridge files that materially implement
that gate are byte-identical. This tool never promotes a gate to PASS; it only
answers whether previously recorded evidence has been invalidated by code
changes.
"""
from __future__ import annotations
import argparse, hashlib, json, time
from pathlib import Path

ROOT=Path(__file__).resolve().parents[1]

def sha256(p:Path)->str:
    h=hashlib.sha256()
    with p.open('rb') as f:
        for b in iter(lambda:f.read(1024*1024),b''): h.update(b)
    return h.hexdigest()

def version()->str:
    return (ROOT/'VERSION').read_text(encoding='utf-8').strip()

# Keep these sets intentionally narrow and explainable. Generated catalogs and
# web styling are excluded because they cannot change canonical multiplayer state.
GATES={
 'transport/session-isolation':[
   'server/index.js','server/telnet.js'
 ],
 'login/tell/save/reconnect':[
   'server/index.js','server/telnet.js',
   'source/upstream/mudlib/adm/daemons/logind.c',
   'source/upstream/mudlib/obj/user.c',
   'source/upstream/mudlib/cmds/std/tell.c',
   'source/upstream/mudlib/cmds/usr/save.c',
   'source/upstream/mudlib/feature/statistic.c',
 ],
 'same-room/say/team/follow':[
   'source/upstream/mudlib/cmds/std/say.c',
   'source/upstream/mudlib/cmds/std/team.c',
   'source/upstream/mudlib/cmds/std/go.c',
   'source/upstream/mudlib/feature/char/team.c',
   'source/upstream/mudlib/feature/char/attack.c',
 ],
 'shared-world/object-ownership':[
   'source/upstream/mudlib/cmds/std/get.c',
   'source/upstream/mudlib/cmds/std/drop.c',
   'source/upstream/mudlib/cmds/std/give.c',
   'source/upstream/mudlib/adm/simul_efun/object.c',
 ],
 'mutual-player-fight':[
   'source/upstream/mudlib/cmds/std/fight.c',
   'source/upstream/mudlib/cmds/std/halt.c',
   'source/upstream/mudlib/feature/char/attack.c',
   'source/upstream/mudlib/feature/char/combat.c',
 ],
 'death/corpse/revival':[
   'source/upstream/mudlib/feature/char/attack.c',
   'source/upstream/mudlib/feature/char/combat.c',
   'source/upstream/mudlib/obj/corpse.c',
 ],
}

def build():
    gates={}; all_missing=[]
    for gate,rels in GATES.items():
        files=[]
        for rel in rels:
            p=ROOT/rel
            if p.exists() and p.is_file(): files.append({'path':rel,'sha256':sha256(p),'bytes':p.stat().st_size})
            else:
                files.append({'path':rel,'missing':True});all_missing.append(rel)
        combo=hashlib.sha256('\n'.join(f"{x['path']}:{x.get('sha256','MISSING')}" for x in files).encode()).hexdigest()
        gates[gate]={'fingerprint':combo,'files':files,'ok':not any(x.get('missing') for x in files)}
    return {'schema':1,'version':version(),'generated':time.strftime('%Y-%m-%dT%H:%M:%S'),'gates':gates,'missing':sorted(set(all_missing)),'ok':not all_missing}

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--output',default='reports/multiplayer_evidence_fingerprint.json');a=ap.parse_args()
    out=build();p=ROOT/a.output;p.parent.mkdir(parents=True,exist_ok=True);p.write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8');print(json.dumps(out,ensure_ascii=False,indent=2));return 0 if out['ok'] else 2
if __name__=='__main__':raise SystemExit(main())
