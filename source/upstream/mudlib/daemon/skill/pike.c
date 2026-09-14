/*---
description: 基本pike技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N挺起$w﹐直刺$n的$l",
    "dodge":       -5,
    "damage":      11,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N踏前一步﹐$w從側面掃向$n的$l",
    "dodge":       -5,
    "damage":      10,
    "damage_type": "瘀傷"
  ]),\n  ([
    "action":      "$N雙臂一送﹐$w疾刺$n的$l",
    "dodge":       -10,
    "damage":      12,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N將$w往回一收﹐隨即挑向$n的$l",
    "dodge":       0,
    "damage":      9,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N側身轉步﹐$w橫掃$n的$l",
    "dodge":       -5,
    "damage":      10,
    "damage_type": "瘀傷"
  ]),\n  ([
    "action":      "$N沉腰發力﹐$w由下往上挑向$n的$l",
    "dodge":       -5,
    "damage":      11,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N向前急跨﹐$w筆直刺向$n的$l",
    "dodge":       -10,
    "damage":      12,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N手中$w一抖﹐槍尖直取$n的$l",
    "dodge":       0,
    "damage":      10,
    "damage_type": "刺傷"
  ])
});

string *interattack = ({
  "$N端著$n﹐槍尖隨著腳步微微晃動。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("pike");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "pike", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
