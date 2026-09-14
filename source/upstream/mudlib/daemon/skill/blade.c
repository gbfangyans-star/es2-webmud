/*---
description: 基本blade技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N手腕一沉﹐$w貼著身側斬向$n的$l",
    "dodge":       0,
    "damage":      8,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N踏前半步﹐手中$w由外往內削向$n的$l",
    "dodge":       -5,
    "damage":      10,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N忽然轉身﹐$w順勢橫斬$n的$l",
    "dodge":       -5,
    "damage":      10,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N將$w一提﹐刀鋒由下往上撩向$n的$l",
    "dodge":       0,
    "damage":      8,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N側身逼近﹐$w斜劈$n的$l",
    "dodge":       -10,
    "damage":      12,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N退後一步又猛然回身﹐$w砍向$n的$l",
    "dodge":       5,
    "damage":      8,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N手中$w劃出一道短弧﹐直削$n的$l",
    "dodge":       0,
    "damage":      9,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N低喝一聲﹐揮動$w直取$n的$l",
    "dodge":       -5,
    "damage":      10,
    "damage_type": "割傷"
  ])
});

string *interattack = ({
  "$N將手中的$n微微一橫﹐緩步移動。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("blade");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "blade", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
