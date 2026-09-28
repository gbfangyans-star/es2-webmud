from pathlib import Path
import json, sys
ROOT=Path(__file__).resolve().parents[1]
M=ROOT/'source/upstream/mudlib'
read=lambda p:(M/p).read_text(encoding='utf-8')
races={r:read(f'daemon/race/{r}.c') for r in ['human','avatar','blackteeth','yenhold','jiaojao','woochan','dingling','headless','rainner','malik']}
cmds={
 'resurge':read('daemon/race/human/resurge.c'),
 'radiate':read('daemon/race/avatar/radiate.c'),
 'gnaw':read('daemon/race/blackteeth/gnaw.c'),
 'breathe':read('daemon/race/yenhold/breathe.c'),
 'hide':read('daemon/race/jiaojao/hide.c'),
 'replete':read('daemon/race/woochan/replete.c'),
 'hoof':read('daemon/race/dingling/hoof.c'),
 'dance':read('daemon/race/headless/dance.c'),
 'feed':read('daemon/race/rainner/feed.c'),
}
cond={c:read(f'custom/race/condition/{c}.c') for c in ['blackteeth_gnaw','headless_dance','headless_ritual']}
soldier=read('daemon/class/soldier.c'); taoist=read('daemon/class/taoist.c')
login=read('adm/daemons/logind.c'); chard=read('adm/daemons/chard.c'); score=read('feature/char/score.c'); chinese=read('data/chinese.o')
checks={
 'all_races_selectable': all(f'"{r}"' in login for r in races if r != 'avatar'),
 'avatar_named_human_clan': '"avatar":"人類族"' in chinese,
 'dingling_chinese': '"dingling":"釘靈"' in chinese,
 'human_birth_stats_35': all(x in races['human'] for x in ['"gin":35','"kee":35','"sen":35']),
 'human_attr_13_18': races['human'].count('13 + random(6)') >= 8,
 'avatar_attr_15_20': races['avatar'].count('15 + random(6)') >= 8,
 'commoner_cap_1': all('"commoner":1,' in s for s in races.values()),
 'headless_cannot_join_monk': '"monk":-1' in races['headless'] and '< 0 )' in score,
 'score_base_values': all(f'"commoner_score_base", {v})' in races[r] or f'"commoner_score_base",{v})' in races[r] for r,v in
     {'human':100,'avatar':100,'blackteeth':120,'yenhold':115,'jiaojao':95,'woochan':100,'dingling':95,'headless':160,'rainner':100,'malik':150}.items()),
 'score_base_used_by_classes': all('query("commoner_score_base")' in c for c in (soldier, taoist)),
 'jiaojao_awareness_dodge': 'add_temp("apply/awarness",100)' in races['jiaojao'] and 'add_temp("apply/dodge",15)' in races['jiaojao'],
 'yenhold_parry': 'add_temp("apply/parry",10)' in races['yenhold'],
 'hide_highest_awareness': 'if (aw > highest) highest = aw;' in cmds['hide'],
 'replete_heals_bars_not_current': all(x in cmds['replete'] for x in ['heal_stat("gin", age)','heal_stat("kee", age)','heal_stat("sen", age)']) and 'supplement_stat("gin"' not in cmds['replete'],
 'replete_hp_fatigue': 'n = 1 + age / 20;' in cmds['replete'] and 'heal_stat("HP", n)' in cmds['replete'],
 'replete_water_cost': 'query_stat_maximum("water") / 6' in cmds['replete'] and 'water_cost > water_now ? water_now : water_cost' in cmds['replete'],
 'replete_busy1_no_cd': 'start_busy(1)' in cmds['replete'] and 'cooldown' not in cmds['replete'].lower(),
 'woochan_food_only_exempt': all(x in races['woochan'] for x in ['set_stat_regenerate("food", TYPE_STATIC)','set_stat_current("food", 0)','set_stat_effective("food", 0)','set_stat_maximum("food", 0)']) and 'set_stat_regenerate("water", TYPE_STATIC)' not in races['woochan'],
 'gnaw_formula': 'damage = 1 + age / 20;' in cmds['gnaw'] and 'duration > 12' in cmds['gnaw'] and 'damage > 15' in cmds['gnaw'],
 'breathe_formula': 'query_stat("kee") / 10 + me->query_attr("cor") * 2' in cmds['breathe'] and 'ob->consume_stat("kee", damage, me)' in cmds['breathe'] and 'me->consume_stat("kee"' not in cmds['breathe'],
 'breathe_cooldown_one_tick': '#define BREATHE_COOLDOWN 2' in cmds['breathe'],
 'hoof_formula': 'consume_stat("kee", damage, me)' in cmds['hoof'] and 'start_busy(2 + random(2))' in cmds['hoof'],
 'dance_five_modes': all(f'case "{m}"' in cmds['dance'] for m in ['glory','fury','axe','sorrow','rite']),
 'dance_not_in_combat': 'is_fighting()' in cmds['dance'],
 'per_tick_call_out': all('call_out(' in c for c in cond.values()),
 'radiate_cooldown_one_minute': '#define RADIATE_COOLDOWN 60' in cmds['radiate'],
 'resurge_quarter_es2_day': '#define RESURGE_COOLDOWN 360' in cmds['resurge'],
 'class_caps_present': all('class_level_cap' in s for s in races.values()),
 'class_caps_enforced': 'query("class_level_cap/" + query_class())' in score,
 'race_hints_present': all(f'case "{r}"' in chard for r in races),
 'rainner_on_command_path': '"/daemon/race/rainner/"' in read('include/command.h'),
 'rainner_snake_bound': all(x in read('custom/race/obj/rainner_snake.c') for x in ['varargs int move(','set_weight(0)','"hand_eq"','* spots / MAX_SPOTS']),
 'rainner_feed_rules': all(x in cmds['feed'] for x in ['20 + random(spots)','"white":  ({ 2, 5, 10, 10 })','"black":  ({ 3, 7, 10, 10 })','start_busy(1)']),
 'malik_chinese': '"malik":"巫首"' in chinese,
 'malik_numbers': all(x in races['malik'] for x in ['set("karma", 30)','"gin":70, "kee":40, "sen":100','"int":25+random(6)','"cps":23+random(6)','"monk":65','add_temp("apply/armor", 40)','add_temp("apply/attack", 30)','add_temp("apply/defense", 30)']),
 'rainner_snake_on_levelup': 'random(2)' in races['rainner'] and 'give_snake' in races['rainner'],
}
fail=[k for k,v in checks.items() if not v]
out={'version':(ROOT/'VERSION').read_text().strip(),'checks':checks,'failures':fail,'passed':not fail}
(ROOT/'reports/custom_race_a_h_audit.json').write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps(out,ensure_ascii=False,indent=2))
sys.exit(0 if not fail else 1)
