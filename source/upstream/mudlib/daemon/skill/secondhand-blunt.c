/*---
description: 基本secondhand blunt技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N左手$w忽然敲向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N側過身去﹐左手$w橫擊$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N右手一晃﹐左手$w趁勢砸向$n的$l",
    "dodge":       0,
    "damage":      7,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N退開半步﹐左手$w反敲$n的$l",
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
    "action":      "$N身子一矮﹐左手$w由下往上敲向$n的$l",
    "dodge":       0,
    "damage":      7,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N突然逼近﹐以左手$w短擊$n的$l",
    "dodge":       0,
    "damage":      7,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N左手腕一轉﹐$w掃向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "瘀傷"
  ])
});

string *interattack = ({
  "$N掂了掂手中的$n﹐尋找出手的時機。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("secondhand blunt");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "secondhand blunt", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
