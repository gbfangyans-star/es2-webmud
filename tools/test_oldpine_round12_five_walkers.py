#!/usr/bin/env python3
import json
from pathlib import Path
R=Path(__file__).resolve().parents[1]/'source/upstream/mudlib/custom/oldpine_recovered'
base=[('room/keep1.c','keep2'),('room/keep2.c','bandit_guard'),('room/keep2.c','pipe_notify'),('room/keep3.c','bandit_commander'),('npc/bandit_commander.c','bamboo_pipe'),('npc/obj/bamboo_pipe.c','pipe_notify'),('room/cliff1.c','riverbank1'),('room/cliff2.c','epath3')]
players=[]
for i in range(1,6):
 ok=True; checks=0
 for lap in range(3):
  for rel,t in base:
   checks+=1
   if t not in (R/rel).read_text(encoding='utf-8',errors='ignore'): ok=False
 players.append({'player':i,'laps':3,'checks':checks,'passed':ok})
out={'mode':'source_level_fallback_NOT_live_neolith','scenario':'keep/cliff/object integration regression','players':players,'total_checks':sum(p['checks'] for p in players),'all_passed':all(p['passed'] for p in players)}
print(json.dumps(out,ensure_ascii=False,indent=2)); raise SystemExit(0 if out['all_passed'] else 1)
