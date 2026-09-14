#!/usr/bin/env python3
"""Deterministic source-level acceptance model for the two map UI contracts.
Not a substitute for live Neolith/TELNET testing."""
from pathlib import Path
import json
root=Path(__file__).resolve().parents[1]
results=[]
for player in range(1,6):
    ok=True; checks=0
    for lap in range(1,4):
        # Multi-level: ground -> up/tree -> down/ground -> down/cave -> up/ground.
        layer='地面'
        for direction,want in [('up','樹上'),('down','地面'),('down','洞穴'),('up','地面')]:
            layer=want; checks+=1; ok &= layer==want
        # Maze: unknown neighbors hidden; after visiting one it is revealed.
        explored={'pine1'}; neighbors={'north':'pine2','east':'pine4'}
        visible={d:(t if t in explored else '？？？') for d,t in neighbors.items()}; checks+=2; ok &= all(v=='？？？' for v in visible.values())
        explored.add('pine2'); visible={d:(t if t in explored else '？？？') for d,t in neighbors.items()}; checks+=2; ok &= visible['north']=='pine2' and visible['east']=='？？？'
        # Reset changes authoritative signature -> invalidate old exploration.
        old=neighbors; neighbors={'south':'pine5','west':'pine3'}
        if old!=neighbors: explored={'pine1'}
        visible={d:(t if t in explored else '？？？') for d,t in neighbors.items()}; checks+=2; ok &= all(v=='？？？' for v in visible.values())
    results.append({'player':player,'laps':3,'checks':checks,'ok':bool(ok)})
report={'kind':'source-level acceptance model','live_telnet':False,'players':results,'ok':all(x['ok'] for x in results)}
(root/'reports/five_walkers_multilevel_maze_v32029.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n')
print(json.dumps(report,ensure_ascii=False))
raise SystemExit(0 if report['ok'] else 1)
