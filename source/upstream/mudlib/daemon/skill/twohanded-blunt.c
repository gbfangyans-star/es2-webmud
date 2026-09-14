/*---
description: 基本twohanded blunt技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N雙手舉起$w﹐狠狠砸向$n的$l",
    "dodge":       -15,
    "damage":      18,
    "damage_type": "瘀傷"
  ]),\n  ([
    "action":      "$N沉腰轉身﹐雙手$w橫掃$n的$l",
    "dodge":       -10,
    "damage":      16,
    "damage_type": "瘀傷"
  ]),\n  ([
    "action":      "$N向前跨步﹐$w帶著沉重力道撞向$n的$l",
    "dodge":       -15,
    "damage":      18,
    "damage_type": "瘀傷"
  ]),\n  ([
    "action":      "$N雙手握緊$w﹐由下往上猛擊$n的$l",
    "dodge":       -10,
    "damage":      16,
    "damage_type": "瘀傷"
  ]),\n  ([
    "action":      "$N大喝一聲﹐$w重重落向$n的$l",
    "dodge":       -20,
    "damage":      20,
    "damage_type": "瘀傷"
  ]),\n  ([
    "action":      "$N身形旋轉﹐雙手$w掃向$n的$l",
    "dodge":       -10,
    "damage":      16,
    "damage_type": "瘀傷"
  ]),\n  ([
    "action":      "$N把$w往後一引﹐再猛力撞向$n的$l",
    "dodge":       -15,
    "damage":      18,
    "damage_type": "瘀傷"
  ]),\n  ([
    "action":      "$N雙臂驟然發力﹐$w直砸$n的$l",
    "dodge":       -15,
    "damage":      18,
    "damage_type": "瘀傷"
  ])
});

string *interattack = ({
  "$N掂了掂手中的$n﹐尋找出手的時機。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("twohanded blunt");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "twohanded blunt", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
