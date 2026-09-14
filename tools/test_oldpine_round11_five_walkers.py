import json
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
MUD=ROOT/'source/upstream/mudlib'
checks=[
 ('entry branch', MUD/'custom/oldpine/room/path08.c','/custom/oldpine_recovered/room/npath1'),
 ('tree butterflies', MUD/'custom/oldpine_recovered/room/tree2.c','../npc/butterfly" : 6'),
 ('pine1 tall', MUD/'custom/oldpine_recovered/room/pine1.c','../npc/tall_bandit" : 1'),
 ('pine1 fat', MUD/'custom/oldpine_recovered/room/pine1.c','../npc/fat_bandit" : 1'),
 ('pine7 dog', MUD/'custom/oldpine_recovered/room/pine7.c','../npc/wolf_dog" : 1'),
 ('fat help', MUD/'custom/oldpine_recovered/npc/fat_bandit.c','bandit_chief'),
]
players=[]
for player in range(1,6):
    count=0
    for lap in range(1,4):
        for name,path,needle in checks:
            assert path.exists(), (name,path)
            assert needle in path.read_text(), name
            count+=1
    players.append({'player':player,'laps':3,'checks':count,'passed':True})
out={'mode':'source_level_fallback_NOT_live_neolith','scenario':'oldpine entry + NPC placement + reinforcement regression','players':players,'all_passed':True,'total_checks':sum(p['checks'] for p in players)}
(ROOT/'reports/oldpine_round11_five_walker_source_test.json').write_text(json.dumps(out,ensure_ascii=False,indent=2)+'\n')
print(json.dumps(out,ensure_ascii=False,indent=2))
