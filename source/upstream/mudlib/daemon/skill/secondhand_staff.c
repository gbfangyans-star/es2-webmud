/*---
description: 基本secondhand staff技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N左手$w忽然掃向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N側身讓步﹐左手$w點向$n的$l",
    "dodge":       10,
    "damage":      5,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N右手微晃﹐左手$w趁勢敲向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N退開半步﹐左手$w反掃$n的$l",
    "dodge":       10,
    "damage":      5,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N左臂一送﹐$w撞向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N身子一矮﹐左手$w由下往上挑向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N突然逼近﹐左手$w短擊$n的$l",
    "dodge":       0,
    "damage":      7,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N左手腕一轉﹐$w橫掃$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "瘀傷"
  ])
});

string *interattack = ({
  "$N握穩$n﹐一邊移步一邊觀察對手。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("secondhand staff");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "secondhand staff", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
