/* CUSTOM RACE: 巫首 (malik). Original race data 2006/09/15. */
#define BASE_WEIGHT 40000
#include <race.h>
inherit HUMANOID;

private void create() {
    ::create(); seteuid(getuid());
    set("karma", 30); set("civilized", 1); set("commoner_score_base", 150);
    set("class_level_cap", ([
        "commoner":1, "fighter":50, "taoist":60, "alchemist":50,
        "soldier":50, "scholar":60, "monk":65, "thief":50
    ]));
    DAEMON_D->register_race_daemon("malik");
}
void setup(object ob) {
    ::setup(ob); ob->set_default_object(__FILE__);
    if (!ob->query_weight()) ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str",1)-13)*5000);
    ob->add_temp("apply/armor", 40);
    ob->add_temp("apply/attack", 30);
    ob->add_temp("apply/defense", 30);
}
void initialize(object ob) {
    ::initialize(ob);
    ob->init_attribute(([
        "str":8+random(4), "cor":8+random(4), "int":25+random(6), "spi":25+random(6),
        "cps":23+random(6), "dex":20+random(6), "con":10+random(6), "wis":20+random(6)
    ]));
    ob->init_statistic(([ "gin":70, "kee":40, "sen":100 ]));
    if (!ob->query("age")) ob->set("age", 14+random(4));
    ob->set_default_object(__FILE__);
}
