#!/usr/bin/env python3
from pathlib import Path
R=Path(__file__).resolve().parents[1]/'source/upstream/mudlib/custom/oldpine_recovered'
checks=[]
def has(rel,*terms):
 s=(R/rel).read_text(encoding='utf-8',errors='ignore'); return all(t in s for t in terms)
checks += [('41 recovered rooms',len(list((R/'room').glob('*.c')))==41),('11 recovered objects',len(list((R/'npc/obj').glob('*.c')))==11)]
for rel,terms in {
'room/keep1.c':('bandit_guard','pine2','keep2'),
'room/keep2.c':('while(i--)','kill_ob(me)','pipe_notify','delete("exits/west")'),
'room/keep3.c':('bandit_leader','bandit_commander'),
'npc/bandit_guard.c':('combat_exp",3600','sword",50','silver",5'),
'npc/bandit_leader.c':('combat_exp",50000','force_factor",4','apply/attack",70'),
'npc/bandit_commander.c':('combat_exp",260000','glaive','fur_coat','bamboo_pipe'),
'npc/obj/bamboo_pipe.c':('add_action("do_play","play")','pipe_notify()'),
'npc/obj/glaive.c':('init_blade(55)',),
'npc/obj/throwing_knife.c':('init_throwing(20)',),
'npc/obj/robe.c':('Archaeology staging only',),
}.items(): checks.append((rel,has(rel,*terms)))
for n,ok in checks: print(('PASS' if ok else 'FAIL'),n)
print(f'{sum(x for _,x in checks)}/{len(checks)} PASS')
raise SystemExit(0 if all(x for _,x in checks) else 1)
