/* CUSTOM A-H RACE: 焦僥 (jiaojao). User-supplied race specification. */
#define BASE_WEIGHT 40000
#include <race.h>
inherit HUMANOID;

private void create() {
    ::create(); seteuid(getuid());
    set("karma",5); set("civilized",1); set("commoner_score_base",100);
    set("class_level_cap", ([
        "commoner":50, "fighter":60, "taoist":50, "alchemist":50,
        "soldier":50, "scholar":65, "monk":65, "thief":65
    ]));
    DAEMON_D->register_race_daemon("jiaojao");
}
void setup(object ob) {
    ::setup(ob); ob->set_default_object(__FILE__);
    if (!ob->query_weight()) ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str",1)-13)*5000);
    ob->add_temp("apply/defense",15);
    ob->add_temp("apply/awarness",100);
}
void initialize(object ob) {
    ::initialize(ob);
    ob->init_attribute(([
        "str":10+random(5), "cor":8+random(6), "int":12+random(8), "spi":12+random(8),
        "cps":15+random(5), "dex":18+random(7), "con":12+random(5), "wis":12+random(7)
    ]));
    ob->init_statistic(([ "gin":40, "kee":25, "sen":25 ]));
    if (!ob->query("age")) ob->set("age",14+random(4));
    ob->set_default_object(__FILE__);
}
