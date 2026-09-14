/*---
description: 基本twohanded sword技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N雙手握緊$w﹐迎面斬向$n的$l",
    "dodge":       -10,
    "damage":      15,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N沉腰踏步﹐雙手$w橫斬$n的$l",
    "dodge":       -10,
    "damage":      14,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N把$w高舉過頂﹐重重劈向$n的$l",
    "dodge":       -15,
    "damage":      17,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N雙手一送﹐$w筆直刺向$n的$l",
    "dodge":       -10,
    "damage":      15,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N身形旋轉﹐雙手$w沿著大弧斬向$n的$l",
    "dodge":       -10,
    "damage":      14,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N退後一步蓄勢﹐再猛然以$w刺向$n的$l",
    "dodge":       -5,
    "damage":      13,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N雙臂一振﹐$w由下往上斜斬$n的$l",
    "dodge":       -10,
    "damage":      15,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N大喝一聲﹐雙手$w直取$n的$l",
    "dodge":       -15,
    "damage":      16,
    "damage_type": "割傷"
  ])
});

string *interattack = ({
  "$N握著$n﹐劍尖隨著身形緩緩移動。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("twohanded sword");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "twohanded sword", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
