/*---
description: 基本secondhand pike技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N左手持$w﹐短促地刺向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "刺傷"
  ]),
  ([
    "action":      "$N側身逼近﹐左手$w掃向$n的$l",
    "dodge":       0,
    "damage":      6,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N右手虛晃﹐左手$w忽然刺向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "刺傷"
  ]),
  ([
    "action":      "$N退開半步﹐左手$w反挑$n的$l",
    "dodge":       10,
    "damage":      5,
    "damage_type": "刺傷"
  ]),
  ([
    "action":      "$N左臂一送﹐$w直取$n的$l",
    "dodge":       0,
    "damage":      7,
    "damage_type": "刺傷"
  ]),
  ([
    "action":      "$N身形一轉﹐左手$w橫掃$n的$l",
    "dodge":       0,
    "damage":      6,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N左手腕一沉﹐$w由下往上挑向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "刺傷"
  ]),
  ([
    "action":      "$N突然前欺﹐左手$w疾刺$n的$l",
    "dodge":       0,
    "damage":      7,
    "damage_type": "刺傷"
  ])
});

string *interattack = ({
  "$N端著$n﹐槍尖隨著腳步微微晃動。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("secondhand pike");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "secondhand pike", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
