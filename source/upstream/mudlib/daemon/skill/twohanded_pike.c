/*---
description: 基本twohanded pike技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N雙手挺起$w﹐猛刺$n的$l",
    "dodge":       -10,
    "damage":      15,
    "damage_type": "刺傷"
  ]),
  ([
    "action":      "$N沉腰跨步﹐雙手$w橫掃$n的$l",
    "dodge":       -10,
    "damage":      14,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N把$w往後一收﹐隨即全力刺向$n的$l",
    "dodge":       -15,
    "damage":      17,
    "damage_type": "刺傷"
  ]),
  ([
    "action":      "$N雙臂一振﹐$w由下往上挑向$n的$l",
    "dodge":       -10,
    "damage":      15,
    "damage_type": "刺傷"
  ]),
  ([
    "action":      "$N大喝一聲﹐$w帶著勁風直取$n的$l",
    "dodge":       -15,
    "damage":      17,
    "damage_type": "刺傷"
  ]),
  ([
    "action":      "$N身形旋轉﹐雙手$w掃向$n的$l",
    "dodge":       -10,
    "damage":      14,
    "damage_type": "瘀傷"
  ]),
  ([
    "action":      "$N向前跨出一大步﹐$w猛刺$n的$l",
    "dodge":       -15,
    "damage":      17,
    "damage_type": "刺傷"
  ]),
  ([
    "action":      "$N雙手一抖﹐$w的尖端直奔$n的$l",
    "dodge":       -10,
    "damage":      15,
    "damage_type": "刺傷"
  ])
});

string *interattack = ({
  "$N端著$n﹐槍尖隨著腳步微微晃動。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("twohanded pike");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "twohanded pike", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
