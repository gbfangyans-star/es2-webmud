/* CUSTOM A-H RACE: 黑齒 (blackteeth). User-supplied race specification. */
#define BASE_WEIGHT 40000
#include <race.h>
inherit HUMANOID;

private void create() {
    ::create(); seteuid(getuid());
    set("karma", 3); set("civilized", 1); set("commoner_score_base", 100);
    set("class_level_cap", ([
        "commoner":50, "fighter":60, "taoist":40, "alchemist":40,
        "soldier":50, "scholar":50, "monk":65, "thief":60
    ]));
    DAEMON_D->register_race_daemon("blackteeth");
}
void setup(object ob) {
    ::setup(ob); ob->set_default_object(__FILE__);
    if (!ob->query_weight()) ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str",1)-13)*5000);
    ob->add_temp("apply/armor", 5);
}
void initialize(object ob) {
    ::initialize(ob);
    ob->init_attribute(([
        "str":15+random(11), "cor":10+random(6), "int":8+random(8), "spi":5+random(6),
        "cps":10+random(6), "dex":12+random(9), "con":12+random(9), "wis":5+random(6)
    ]));
    ob->init_statistic(([ "gin":35, "kee":25, "sen":10 ]));
    if (!ob->query("age")) ob->set("age",14+random(4));
    ob->set_default_object(__FILE__);
}
