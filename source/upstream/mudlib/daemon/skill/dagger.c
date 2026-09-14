/*---
description: 基本dagger技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N握緊$w﹐迅速刺向$n的$l",
    "dodge":       5,
    "damage":      7,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N側身貼近﹐$w斜刺$n的$l",
    "dodge":       0,
    "damage":      8,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N手腕一翻﹐$w由下往上挑向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N退後半步﹐忽然前欺以$w刺向$n的$l",
    "dodge":       0,
    "damage":      8,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N將$w藏在身側﹐冷不防直取$n的$l",
    "dodge":       -5,
    "damage":      9,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N身子一矮﹐$w從側面刺向$n的$l",
    "dodge":       5,
    "damage":      7,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N腳下一錯﹐$w順勢劃向$n的$l",
    "dodge":       5,
    "damage":      6,
    "damage_type": "割傷"
  ]),\n  ([
    "action":      "$N忽然伸臂﹐手中$w疾刺$n的$l",
    "dodge":       0,
    "damage":      8,
    "damage_type": "刺傷"
  ])
});

string *interattack = ({
  "$N把$n收在身側﹐腳下悄悄挪動。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("dagger");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "dagger", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
