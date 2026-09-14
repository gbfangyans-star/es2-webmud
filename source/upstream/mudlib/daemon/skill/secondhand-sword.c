/*---
description: 基本secondhand sword技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N左手$w輕輕一抖﹐刺向$n的$l",
    "dodge":       10,
    "damage":      5,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N右手虛晃﹐左手$w忽然削向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N側身逼近﹐左手$w斜刺$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N退後半步﹐左手$w反手刺向$n的$l",
    "dodge":       10,
    "damage":      5,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N左腕一轉﹐$w劃向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N身子一矮﹐左手$w由下往上挑向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N突然轉身﹐左手$w斬向$n的$l",
    "dodge":       0,
    "damage":      7,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N左手一送﹐$w直取$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "刺傷"
  ])
});

string *interattack = ({
  "$N握著$n﹐劍尖隨著身形緩緩移動。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("secondhand sword");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "secondhand sword", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
