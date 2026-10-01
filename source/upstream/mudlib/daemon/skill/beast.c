/*---
description: 野獸的徒手攻擊。野獸種族（daemon/race/beast.c）把 unarmed 對應到這裡，
             攻擊時用種族的咬、撞、踢等動作，而不是人形的拳腳招式。
---*/
#include <ansi.h>

inherit SKILL;

private void create() {
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("beast");
    setup();
}

void attack_using(object me, object opponent, string skill) {
    if( !opponent ) return;
    COMBAT_D->fight(me, opponent, "unarmed", RACE_D(me->query_race())->query_action());
}

int valid_enable(string usage) { return usage == "unarmed"; }
