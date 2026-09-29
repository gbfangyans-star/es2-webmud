/* CUSTOM A-H RACE: 黑齒 (blackteeth). User-supplied race specification. */
#define BASE_WEIGHT 40000
#include <race.h>
inherit HUMANOID;

private void create() {
    ::create(); seteuid(getuid());
    set("karma", 3); set("civilized", 1); set("commoner_score_base", 120);
    set("class_level_cap", ([
        "commoner":1, "fighter":55, "taoist":40, "alchemist":45,
        "soldier":60, "scholar":40, "monk":65, "thief":55
    ]));
    DAEMON_D->register_race_daemon("blackteeth");
}
void setup(object ob) {
    ::setup(ob); ob->set_default_object(__FILE__);
    if (!ob->query_weight()) ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str",1)-13)*5000);
    ob->add_temp("apply/armor", 3);
}
void initialize(object ob) {
    ::initialize(ob);
    ob->init_attribute(([
        "str":14+random(6), "cor":15+random(6), "int":5+random(11), "spi":3+random(6),
        "cps":10+random(6), "dex":11+random(6), "con":13+random(6), "wis":6+random(6)
    ]));
    ob->init_statistic(([ "gin":35, "kee":25, "sen":10 ]));
    if (!ob->query("age")) ob->set("age",14+random(4));
    ob->set_default_object(__FILE__);
}
