/*---
description: 基本blunt技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N掄起$w﹐重重砸向$n的$l",
    "dodge":       -10,
    "damage":      14,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N踏前一步﹐$w橫掃$n的$l",
    "dodge":       -5,
    "damage":      12,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N沉肩發力﹐$w由下往上撞向$n的$l",
    "dodge":       -5,
    "damage":      10,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N將$w一提﹐突然敲向$n的$l",
    "dodge":       0,
    "damage":      9,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N大喝一聲﹐手中$w猛擊$n的$l",
    "dodge":       -10,
    "damage":      14,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N側身逼近﹐$w短促地砸向$n的$l",
    "dodge":       0,
    "damage":      10,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N手腕一翻﹐$w從側面敲向$n的$l",
    "dodge":       5,
    "damage":      8,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N向前一步﹐用$w狠狠撞向$n的$l",
    "dodge":       -5,
    "damage":      12,
    "damage_type": "瘀傷"
  ])
});

string *interattack = ({
  "$N掂了掂手中的$n﹐尋找出手的時機。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("blunt");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "blunt", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
