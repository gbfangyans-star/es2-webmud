/*---
description: 基本twohanded blade技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N雙手握住$w﹐猛然劈向$n的$l",
    "dodge":       -10,
    "damage":      15,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N沉腰跨步﹐雙手$w橫斬$n的$l",
    "dodge":       -10,
    "damage":      14,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N把$w高舉過頂﹐重重砍向$n的$l",
    "dodge":       -15,
    "damage":      17,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N身形一轉﹐雙手$w沿著大弧斬向$n的$l",
    "dodge":       -10,
    "damage":      14,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N向前猛踏一步﹐$w斜斬$n的$l",
    "dodge":       -15,
    "damage":      16,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N雙手把$w往後一引﹐隨即全力劈向$n的$l",
    "dodge":       -15,
    "damage":      17,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N低身蓄力﹐$w由下往上猛撩$n的$l",
    "dodge":       -10,
    "damage":      15,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N雙臂一振﹐$w帶著勁風直取$n的$l",
    "dodge":       -10,
    "damage":      15,
    "damage_type": "割傷"
  ])
});

string *interattack = ({
  "$N將手中的$n微微一橫﹐緩步移動。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("twohanded blade");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "twohanded blade", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
