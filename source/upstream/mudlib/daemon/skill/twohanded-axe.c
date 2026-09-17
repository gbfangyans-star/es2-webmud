/*---
description: 基本twohanded axe技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N雙手高舉$w﹐挾著全身力道劈向$n的$l",
    "dodge":       -15,
    "damage":      18,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N沉腰轉胯﹐雙手$w橫掃$n的$l",
    "dodge":       -10,
    "damage":      16,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N向前跨出一大步﹐$w由上往下猛斬$n的$l",
    "dodge":       -20,
    "damage":      20,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N雙手握緊$w﹐從腰側猛然撩向$n的$l",
    "dodge":       -10,
    "damage":      16,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N大喝一聲﹐$w帶著沉重風聲砍向$n的$l",
    "dodge":       -15,
    "damage":      18,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N身形旋轉﹐雙手$w劃出大弧斬向$n的$l",
    "dodge":       -10,
    "damage":      16,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N把$w往後一引﹐再全力劈向$n的$l",
    "dodge":       -20,
    "damage":      20,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N雙臂驟然發力﹐$w直取$n的$l",
    "dodge":       -15,
    "damage":      18,
    "damage_type": "割傷"
  ])
});

string *interattack = ({
  "$N握著手中的$n﹐目光盯著對手的破綻。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("twohanded axe");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "twohanded axe", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
