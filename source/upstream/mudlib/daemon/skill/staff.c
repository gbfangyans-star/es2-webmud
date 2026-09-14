/*---
description: 基本staff技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N揮動$w﹐橫掃$n的$l",
    "dodge":       -5,
    "damage":      10,
    "damage_type": "瘀傷"
  ]),\n  ([
    "action":      "$N踏前一步﹐$w直點$n的$l",
    "dodge":       0,
    "damage":      8,
    "damage_type": "瘀傷"
  ]),\n  ([
    "action":      "$N將$w一提﹐由上往下敲向$n的$l",
    "dodge":       -5,
    "damage":      10,
    "damage_type": "瘀傷"
  ]),\n  ([
    "action":      "$N側身旋轉﹐$w順勢掃向$n的$l",
    "dodge":       -5,
    "damage":      10,
    "damage_type": "瘀傷"
  ]),\n  ([
    "action":      "$N雙臂一送﹐$w的前端撞向$n的$l",
    "dodge":       0,
    "damage":      9,
    "damage_type": "瘀傷"
  ]),\n  ([
    "action":      "$N退開一步﹐忽然回身以$w敲向$n的$l",
    "dodge":       5,
    "damage":      8,
    "damage_type": "瘀傷"
  ]),\n  ([
    "action":      "$N身子一矮﹐$w貼地掃向$n的$l",
    "dodge":       -10,
    "damage":      11,
    "damage_type": "瘀傷"
  ]),\n  ([
    "action":      "$N低喝一聲﹐手中$w猛擊$n的$l",
    "dodge":       -5,
    "damage":      10,
    "damage_type": "瘀傷"
  ])
});

string *interattack = ({
  "$N握穩$n﹐一邊移步一邊觀察對手。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("staff");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "staff", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
