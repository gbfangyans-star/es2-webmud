/* CUSTOM A-H RACE: 釘靈 (dingling). User-supplied race specification. */
#define BASE_WEIGHT 40000
#include <race.h>
inherit HUMANOID;

private void create() {
    ::create(); seteuid(getuid());
    set("karma",10); set("civilized",1); set("commoner_score_base",100);
    set("class_level_cap", ([
        "commoner":50, "fighter":60, "taoist":50, "alchemist":50,
        "soldier":65, "scholar":50, "monk":65, "thief":60
    ]));
    DAEMON_D->register_race_daemon("dingling");
}
void setup(object ob) {
    ::setup(ob); ob->set_default_object(__FILE__);
    if (!ob->query_weight()) ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str",1)-13)*5000);
    ob->add_temp("apply/move",50);
    ob->add_temp("apply/damage",10);
}
void initialize(object ob) {
    ::initialize(ob);
    ob->init_attribute(([
        "str":15+random(6), "cor":10+random(6), "int":10+random(6), "spi":8+random(3),
        "cps":12+random(9), "dex":20+random(6), "con":15+random(6), "wis":10+random(6)
    ]));
    ob->init_statistic(([ "gin":70, "kee":40, "sen":20 ]));
    if (!ob->query("age")) ob->set("age",14+random(4));
    ob->set_default_object(__FILE__);
}
