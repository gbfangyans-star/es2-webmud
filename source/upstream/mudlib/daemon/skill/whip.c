/*---
description: 基本whip技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N手腕一抖﹐$w捲向$n的$l",
    "dodge":       0,
    "damage":      9,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N側身甩動$w﹐鞭梢抽向$n的$l",
    "dodge":       5,
    "damage":      8,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N向後一帶$w﹐忽然反抽$n的$l",
    "dodge":       5,
    "damage":      8,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N踏前一步﹐$w劃出一道弧線掃向$n的$l",
    "dodge":       0,
    "damage":      9,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N手臂一揚﹐$w從上往下抽向$n的$l",
    "dodge":       -5,
    "damage":      10,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N身形一轉﹐$w繞過身側捲向$n的$l",
    "dodge":       5,
    "damage":      8,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N猛然抖腕﹐$w的鞭梢直取$n的$l",
    "dodge":       0,
    "damage":      9,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N退後半步﹐手中$w隨即橫抽$n的$l",
    "dodge":       5,
    "damage":      8,
    "damage_type": "割傷"
  ])
});

string *interattack = ({
  "$N垂著手中的$n﹐鞭梢在地面輕輕晃動。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("whip");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "whip", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
