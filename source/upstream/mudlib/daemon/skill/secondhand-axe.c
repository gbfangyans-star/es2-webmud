/*---
description: 基本secondhand axe技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N左手一翻﹐$w從側面劈向$n的$l",
    "dodge":       5,
    "damage":      5,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N身形一晃﹐左手$w貼近$n的$l削去",
    "dodge":       0,
    "damage":      6,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N右肩微沉作勢﹐左手$w忽然斬向$n的$l",
    "dodge":       5,
    "damage":      5,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N退開半步﹐左手$w反手撩向$n的$l",
    "dodge":       10,
    "damage":      4,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N左臂一送﹐$w短促地劈向$n的$l",
    "dodge":       0,
    "damage":      6,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N側身逼近﹐以左手$w橫斬$n的$l",
    "dodge":       -5,
    "damage":      7,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N左手腕一轉﹐$w沿著弧線削向$n的$l",
    "dodge":       5,
    "damage":      5,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N突然低身﹐左手$w斜斜砍向$n的$l",
    "dodge":       0,
    "damage":      6,
    "damage_type": "割傷"
  ])
});

string *interattack = ({
  "$N握著手中的$n﹐目光盯著對手的破綻。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("secondhand axe");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "secondhand axe", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
