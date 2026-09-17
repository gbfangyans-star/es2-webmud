/*---
description: 基本axe技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N掄起$w﹐朝$n的$l猛劈下去",
    "dodge":       -10,
    "damage":      12,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N踏前一步﹐手中$w橫掃$n的$l",
    "dodge":       -5,
    "damage":      10,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N扭腰發力﹐$w由下往上撩向$n的$l",
    "dodge":       -10,
    "damage":      12,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N將$w往肩上一扛﹐忽然斜斬$n的$l",
    "dodge":       0,
    "damage":      8,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N雙臂一沉﹐$w重重剁向$n的$l",
    "dodge":       -15,
    "damage":      15,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N側身讓步﹐順勢用$w削向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N低喝一聲﹐$w劃出半圓斬向$n的$l",
    "dodge":       -5,
    "damage":      10,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N猛然欺近﹐以$w迎面劈向$n的$l",
    "dodge":       -10,
    "damage":      12,
    "damage_type": "割傷"
  ])
});

string *interattack = ({
  "$N握著手中的$n﹐目光盯著對手的破綻。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("axe");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "axe", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
