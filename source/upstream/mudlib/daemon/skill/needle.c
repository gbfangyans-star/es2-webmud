/*---
description: 基本needle技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N兩指夾住$w﹐抖手射向$n的$l",
    "dodge":       10,
    "damage":      5,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N手腕輕彈﹐$w直取$n的$l",
    "dodge":       10,
    "damage":      5,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N側身一讓﹐順勢將$w送向$n的$l",
    "dodge":       15,
    "damage":      4,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N指尖一轉﹐$w忽然刺向$n的$l",
    "dodge":       10,
    "damage":      5,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N假意後退﹐冷不防以$w點向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N手臂微抬﹐$w從袖旁疾出刺向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N腳下一移﹐$w貼著側面刺向$n的$l",
    "dodge":       10,
    "damage":      5,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N凝神看準空隙﹐以$w直刺$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "刺傷"
  ])
});

string *interattack = ({
  "$N指間扣著$n﹐凝神注視前方。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("needle");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "needle", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
