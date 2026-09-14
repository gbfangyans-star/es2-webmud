/*---
description: 基本secondhand needle技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N左指夾住$w﹐輕巧地刺向$n的$l",
    "dodge":       15,
    "damage":      3,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N右手微晃﹐左手$w趁勢點向$n的$l",
    "dodge":       10,
    "damage":      4,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N左腕一抖﹐$w疾取$n的$l",
    "dodge":       10,
    "damage":      4,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N退開半步﹐左手$w忽然刺向$n的$l",
    "dodge":       15,
    "damage":      3,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N側身靠近﹐左手$w貼著空隙送向$n的$l",
    "dodge":       10,
    "damage":      4,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N左手一翻﹐$w由下往上點向$n的$l",
    "dodge":       10,
    "damage":      4,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N身形一晃﹐左手$w從側面刺向$n的$l",
    "dodge":       10,
    "damage":      4,
    "damage_type": "刺傷"
  ]),\n  ([
    "action":      "$N趁$n稍一分神﹐左手$w迅速刺向$n的$l",
    "dodge":       5,
    "damage":      5,
    "damage_type": "刺傷"
  ])
});

string *interattack = ({
  "$N指間扣著$n﹐凝神注視前方。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("secondhand needle");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "secondhand needle", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
