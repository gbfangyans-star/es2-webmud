/* CUSTOM A-H RACE: 厭火 (yenhold). User-supplied race specification. */
#define BASE_WEIGHT 40000
#include <race.h>
inherit HUMANOID;

private void create() {
    ::create(); seteuid(getuid());
    set("karma",5); set("civilized",1); set("commoner_score_base",100);
    set("class_level_cap", ([
        "commoner":50, "fighter":60, "taoist":40, "alchemist":40,
        "soldier":60, "scholar":50, "monk":65, "thief":50
    ]));
    DAEMON_D->register_race_daemon("yenhold");
}
void setup(object ob) {
    ::setup(ob); ob->set_default_object(__FILE__);
    if (!ob->query_weight()) ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str",1)-13)*5000);
    ob->add_temp("apply/armor",20);
    ob->add_temp("apply/armor_vs_fire",50);
}
void initialize(object ob) {
    ::initialize(ob);
    ob->init_attribute(([
        "str":15+random(6), "cor":8+random(7), "int":5+random(6), "spi":8+random(5),
        "cps":15+random(6), "dex":8+random(7), "con":16+random(7), "wis":10+random(6)
    ]));
    ob->init_statistic(([ "gin":20, "kee":30, "sen":20 ]));
    if (!ob->query("age")) ob->set("age",14+random(4));
    ob->set_default_object(__FILE__);
}
