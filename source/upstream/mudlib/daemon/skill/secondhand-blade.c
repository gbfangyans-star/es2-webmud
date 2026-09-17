/*---
description: 基本secondhand blade技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N左手$w輕輕一晃﹐忽然削向$n的$l",
    "dodge":       5,
    "damage":      5,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N側過身去﹐左手$w反斬$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N右手虛晃﹐左手$w趁勢劈向$n的$l",
    "dodge":       0,
    "damage":      6,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N退開半步﹐左手$w由下往上撩向$n的$l",
    "dodge":       10,
    "damage":      4,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N左腕一翻﹐$w斜斜削過$n的$l",
    "dodge":       5,
    "damage":      5,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N身子一矮﹐左手$w橫斬$n的$l",
    "dodge":       0,
    "damage":      6,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N忽然欺近﹐左手$w短促地砍向$n的$l",
    "dodge":       -5,
    "damage":      7,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N左手$w貼身一轉﹐反手斬向$n的$l",
    "dodge":       5,
    "damage":      5,
    "damage_type": "割傷"
  ])
});

string *interattack = ({
  "$N將手中的$n微微一橫﹐緩步移動。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("secondhand blade");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "secondhand blade", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
