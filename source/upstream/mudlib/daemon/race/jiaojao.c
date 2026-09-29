/* CUSTOM A-H RACE: 焦僥 (jiaojao). User-supplied race specification. */
#define BASE_WEIGHT 40000
#include <race.h>
inherit HUMANOID;

private void create() {
    ::create(); seteuid(getuid());
    set("karma",10); set("civilized",1); set("commoner_score_base",95);
    set("class_level_cap", ([
        "commoner":1, "fighter":50, "taoist":40, "alchemist":40,
        "soldier":50, "scholar":65, "monk":65, "thief":60
    ]));
    DAEMON_D->register_race_daemon("jiaojao");
}
void setup(object ob) {
    ::setup(ob); ob->set_default_object(__FILE__);
    if (!ob->query_weight()) ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str",1)-13)*5000);
    ob->add_temp("apply/awarness",100);
    ob->add_temp("apply/dodge",15);      // 縱躍閃躲之法 +15（技能等級）
}
void initialize(object ob) {
    ::initialize(ob);
    ob->init_attribute(([
        "str":8+random(7), "cor":8+random(6), "int":16+random(4), "spi":13+random(7),
        "cps":13+random(7), "dex":18+random(7), "con":11+random(6), "wis":13+random(6)
    ]));
    ob->init_statistic(([ "gin":40, "kee":25, "sen":25 ]));
    if (!ob->query("age")) ob->set("age",14+random(4));
    ob->set_default_object(__FILE__);
}
