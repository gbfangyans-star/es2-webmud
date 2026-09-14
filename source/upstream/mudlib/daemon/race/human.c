/*---
description: 人類種族的定義。
author: Annihilator <taedlar@gmail.com>
custom: WebMUD A-H race rebalance based on user-supplied 種族設定表.
---*/
#define BASE_WEIGHT 40000

#include <ansi.h>
#include <statistic.h>
#include <race.h>

inherit HUMANOID;

private void create() {
    ::create();

    seteuid(getuid());
    set("karma", 5);
    set("civilized", 1);
    set("commoner_score_base", 100);
    set("class_level_cap", ([
        "commoner":50, "fighter":60, "taoist":50, "alchemist":60,
        "soldier":50, "scholar":70, "monk":65, "thief":50
    ]));

    DAEMON_D->register_race_daemon("human");
}

void setup(object ob) {
    ::setup(ob);

    ob->set_default_object(__FILE__);
    if (!ob->query_weight())
        ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str", 1) - 13) * 5000);

    ob->add_temp("apply/armor", 10);
}

void initialize(object ob) {
    ::initialize(ob);

    // New-race rule: human creation has a 0.01% chance to become avatar.
    if (base_name(ob) == USER_OB && random(10000) == 9999) {
        ob->set_race("avatar");
        return;
    }

    ob->init_attribute(([
        "str":12 + random(7), "cor":12 + random(7),
        "int":12 + random(7), "spi":12 + random(7),
        "cps":12 + random(7), "dex":12 + random(7),
        "con":12 + random(7), "wis":12 + random(7)
    ]));

    ob->init_statistic(([ "gin":35, "kee":35, "sen":35 ]));

    if (!ob->query("age")) ob->set("age", 14 + random(4));
    ob->set_default_object(__FILE__);
}
