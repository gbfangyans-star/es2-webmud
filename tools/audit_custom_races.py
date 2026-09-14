from pathlib import Path
import json, sys
ROOT=Path(__file__).resolve().parents[1]
M=ROOT/'source/upstream/mudlib'
read=lambda p:(M/p).read_text(encoding='utf-8')
races={r:read(f'daemon/race/{r}.c') for r in ['human','avatar','blackteeth','yenhold','jiaojao','woochan','dingling']}
cmds={
 'resurge':read('daemon/race/human/resurge.c'),
 'radiate':read('daemon/race/avatar/radiate.c'),
 'gnaw':read('daemon/race/blackteeth/gnaw.c'),
 'breathe':read('daemon/race/yenhold/breathe.c'),
 'hide':read('daemon/race/jiaojao/hide.c'),
 'replete':read('daemon/race/woochan/replete.c'),
 'hoof':read('daemon/race/dingling/hoof.c'),
}
login=read('adm/daemons/logind.c'); chard=read('adm/daemons/chard.c'); score=read('feature/char/score.c'); chinese=read('data/chinese.o')
checks={
 'all_seven_races_selectable': all(f'"{r}"' in login for r in races),
 'avatar_named_human_clan': '"avatar":"人類族"' in chinese,
 'dingling_chinese': '"dingling":"釘靈"' in chinese,
 'human_birth_stats_35': all(x in races['human'] for x in ['"gin":35','"kee":35','"sen":35']),
 'human_attr_12_random7': races['human'].count('12 + random(7)') >= 8,
 'avatar_karma5': 'set("karma", 5)' in races['avatar'],
 'avatar_attr_15_random6': races['avatar'].count('15 + random(6)') >= 8,
 'passive_defense_dynamic': 'add_temp("apply/defense",15)' in races['jiaojao'],
 'action_move_standard': 'add_temp("apply/move",50)' in races['dingling'] and 'query_ability("move")' in cmds['hoof'],
 'hide_highest_awareness': 'if (aw > highest) highest = aw;' in cmds['hide'],
 'replete_heals_bars_not_current': all(x in cmds['replete'] for x in ['heal_stat("gin", age)','heal_stat("kee", age)','heal_stat("sen", age)']) and 'supplement_stat("gin"' not in cmds['replete'],
 'replete_water_cost': 'query_stat_maximum("water") / 3' in cmds['replete'] and 'water_cost > water_now ? water_now : water_cost' in cmds['replete'],
 'replete_busy1_no_cd': 'start_busy(1)' in cmds['replete'] and 'cooldown' not in cmds['replete'].lower(),
 'woochan_food_only_exempt': all(x in races['woochan'] for x in ['set_stat_regenerate("food", TYPE_STATIC)','set_stat_current("food", 0)','set_stat_effective("food", 0)','set_stat_maximum("food", 0)']) and 'set_stat_regenerate("water", TYPE_STATIC)' not in races['woochan'],
 'gnaw_min_one_integer': 'if (duration < 1) duration = 1;' in cmds['gnaw'] and 'target_age / 2' in cmds['gnaw'] and 'target_age / 4' in cmds['gnaw'],
 'breathe_formula': 'query_stat_maximum("kee") / 12' in cmds['breathe'] and 'query_stat_maximum("kee") / 10' in cmds['breathe'] and 'me->query("age") + min_dam' in cmds['breathe'],
 'two_tick_is_four_seconds': '#define RADIATE_COOLDOWN 4' in cmds['radiate'] and '#define BREATHE_COOLDOWN 4' in cmds['breathe'],
 'resurge_quarter_es2_day': '#define RESURGE_COOLDOWN 360' in cmds['resurge'],
 'class_caps_present': all('class_level_cap' in s for s in races.values()),
 'class_caps_enforced': 'query("class_level_cap/" + query_class())' in score,
 'race_hints_present': all(f'case "{r}"' in chard for r in ['human','avatar','blackteeth','yenhold','jiaojao','woochan','dingling']),
}
fail=[k for k,v in checks.items() if not v]
out={'version':(ROOT/'VERSION').read_text().strip(),'checks':checks,'failures':fail,'passed':not fail}
(ROOT/'reports/custom_race_a_h_audit.json').write_text(json.dumps(out,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps(out,ensure_ascii=False,indent=2))
sys.exit(0 if not fail else 1)
