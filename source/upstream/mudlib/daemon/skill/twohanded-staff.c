/*---
description: 基本twohanded staff技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N雙手握住$w﹐猛然橫掃$n的$l",
    "dodge":       -10,
    "damage":      15,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N沉腰跨步﹐雙手$w直撞$n的$l",
    "dodge":       -10,
    "damage":      14,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N把$w高舉過頂﹐重重敲向$n的$l",
    "dodge":       -15,
    "damage":      17,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N身形一轉﹐雙手$w掃出大弧擊向$n的$l",
    "dodge":       -10,
    "damage":      15,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N雙臂一送﹐$w前端猛撞$n的$l",
    "dodge":       -10,
    "damage":      15,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N向後一引$w﹐隨即全力敲向$n的$l",
    "dodge":       -15,
    "damage":      17,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N低身旋步﹐$w貼地掃向$n的$l",
    "dodge":       -15,
    "damage":      16,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N大喝一聲﹐雙手$w猛擊$n的$l",
    "dodge":       -10,
    "damage":      15,
    "damage_type": "瘀傷"
  ])
});

string *interattack = ({
  "$N握穩$n﹐一邊移步一邊觀察對手。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("twohanded staff");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "twohanded staff", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
