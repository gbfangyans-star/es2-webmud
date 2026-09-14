#!/usr/bin/env python3
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
M=ROOT/'source/upstream/mudlib'
checks=[]
def text(p): return (M/p).read_text(encoding='utf-8',errors='replace')
def ck(name, ok): checks.append((name,bool(ok)))
get=text('cmds/std/get.c'); drop=text('cmds/std/drop.c'); give=text('cmds/std/give.c')
attack=text('feature/char/attack.c'); stat=text('feature/statistic.c'); humanoid=text('std/race/humanoid.c'); npc=text('std/char/npc.c')
ck('ground get moves the one canonical object into player inventory','obj->move(me)' in get)
ck('get rejects living targets instead of treating players as loot','living(obj)' in get and '你附近沒有這樣東西' in get)
ck('guarded ground objects reject other takers','query_temp("guarded")' in get and '防止任何人拿走' in get)
ck('drop moves the canonical object into the shared room','obj->move(environment(me))' in drop)
ck('give resolves a target in the current shared room','present(target, environment(me))' in give)
ck('give refuses self-transfer','who==me' in give)
ck('give refuses no_drop objects','query("no_drop")' in give and '不能隨便給人' in give)
ck('give transfers the same object to recipient','item->move(who)' in give)
ck('combat enemy state is per character and supports multiple opponents','enemy +=' in attack and 'member_array(ob, enemy)' in attack)
ck('guardians can join a shared target fight','wake_guard(this_object())' in attack and 'activate_guard(this_object())' in attack)
ck('damage attribution stores the actual last source object','last_damage_giver()' in stat and 'last_from_ob' in stat)
ck('death consumes last damage giver as canonical killer', 'killer = ob->last_damage_giver()' in humanoid)
ck('NPC bounty is awarded to last damage giver','last_damage_giver()' in npc and 'gain_score' in npc)
for n,o in checks: print(('[PASS] ' if o else '[FAIL] ')+n)
print(f'\n{sum(o for _,o in checks)}/{len(checks)} canonical shared-world contracts passed')
raise SystemExit(0 if all(o for _,o in checks) else 1)
