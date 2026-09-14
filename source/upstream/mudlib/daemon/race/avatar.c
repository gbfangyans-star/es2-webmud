/*---
description: 人類族（avatar）的定義。
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
        "commoner":70, "fighter":70, "taoist":70, "alchemist":70,
        "soldier":70, "scholar":70, "monk":70, "thief":70
    ]));

    DAEMON_D->register_race_daemon("avatar");
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

    ob->init_attribute(([
        "str":15 + random(6), "cor":15 + random(6),
        "int":15 + random(6), "spi":15 + random(6),
        "cps":15 + random(6), "dex":15 + random(6),
        "con":15 + random(6), "wis":15 + random(6)
    ]));
    ob->init_statistic(([ "gin":30, "kee":30, "sen":30 ]));

    if (!ob->query("age")) ob->set("age", 14 + random(4));
    ob->set_default_object(__FILE__);
}
