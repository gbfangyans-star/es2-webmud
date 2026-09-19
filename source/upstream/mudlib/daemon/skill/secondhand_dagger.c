/*---
description: 基本secondhand dagger技能的戰鬥動作定義。
author: ES2 WebMUD rebuild
---*/
#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":      "$N左手$w輕輕一送﹐刺向$n的$l",
    "dodge":       10,
    "damage":      4,
    "damage_type": "刺傷"
  ]),
  ([
    "action":      "$N右手虛晃﹐左手$w忽然刺向$n的$l",
    "dodge":       5,
    "damage":      5,
    "damage_type": "刺傷"
  ]),
  ([
    "action":      "$N側身閃進﹐左手$w挑向$n的$l",
    "dodge":       10,
    "damage":      4,
    "damage_type": "刺傷"
  ]),
  ([
    "action":      "$N退開半步﹐左手$w反刺$n的$l",
    "dodge":       10,
    "damage":      4,
    "damage_type": "刺傷"
  ]),
  ([
    "action":      "$N左腕一轉﹐$w劃向$n的$l",
    "dodge":       5,
    "damage":      5,
    "damage_type": "割傷"
  ]),
  ([
    "action":      "$N身子一矮﹐左手$w貼近$n的$l刺去",
    "dodge":       5,
    "damage":      5,
    "damage_type": "刺傷"
  ]),
  ([
    "action":      "$N忽然轉身﹐左手$w由側面刺向$n的$l",
    "dodge":       5,
    "damage":      5,
    "damage_type": "刺傷"
  ]),
  ([
    "action":      "$N左手$w一閃﹐疾取$n的$l",
    "dodge":       5,
    "damage":      5,
    "damage_type": "刺傷"
  ])
});

string *interattack = ({
  "$N把$n收在身側﹐腳下悄悄挪動。\n"
});

private void create() {
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("secondhand dagger");
  setup();
}

void attack_using(object me, object opponent, object weapon) {
  if (!opponent) {
    if (me->query_temp("last_attacked_target"))
      message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
    return;
  }

  COMBAT_D->fight(me, opponent, "secondhand dagger", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage) {
  return 0;
}
