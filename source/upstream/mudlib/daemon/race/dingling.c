/* CUSTOM A-H RACE: 釘靈 (dingling). User-supplied race specification. */
#define BASE_WEIGHT 40000
#include <race.h>
inherit HUMANOID;

private void create() {
    ::create(); seteuid(getuid());
    set("karma",10); set("civilized",1); set("commoner_score_base",95);
    set("class_level_cap", ([
        "commoner":1, "fighter":55, "taoist":50, "alchemist":50,
        "soldier":65, "scholar":50, "monk":65, "thief":60
    ]));
    DAEMON_D->register_race_daemon("dingling");
}
void setup(object ob) {
    ::setup(ob); ob->set_default_object(__FILE__);
    if (!ob->query_weight()) ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str",1)-13)*5000);
    ob->add_temp("apply/armor",5);
    ob->add_temp("apply/intimidate",15);
    ob->add_temp("apply/damage",5);
}
void initialize(object ob) {
    ::initialize(ob);
    ob->init_attribute(([
        "str":14+random(7), "cor":8+random(4), "int":11+random(8), "spi":8+random(4),
        "cps":8+random(10), "dex":17+random(9), "con":14+random(7), "wis":12+random(5)
    ]));
    ob->init_statistic(([ "gin":70, "kee":40, "sen":20 ]));
    if (!ob->query("age")) ob->set("age",14+random(4));
    ob->set_default_object(__FILE__);
}
