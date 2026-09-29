/* CUSTOM A-H RACE: 厭火 (yenhold). User-supplied race specification. */
#define BASE_WEIGHT 40000
#include <race.h>
inherit HUMANOID;

private void create() {
    ::create(); seteuid(getuid());
    set("karma",5); set("civilized",1); set("commoner_score_base",115);
    set("class_level_cap", ([
        "commoner":1, "fighter":55, "taoist":40, "alchemist":35,
        "soldier":55, "scholar":40, "monk":65, "thief":55
    ]));
    DAEMON_D->register_race_daemon("yenhold");
}
void setup(object ob) {
    ::setup(ob); ob->set_default_object(__FILE__);
    if (!ob->query_weight()) ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str",1)-13)*5000);
    ob->add_temp("apply/armor",5);
    ob->add_temp("apply/armor_vs_fire",50);
    ob->add_temp("apply/parry",10);      // 拆招卸力之法 +10（技能等級）
}
void initialize(object ob) {
    ::initialize(ob);
    ob->init_attribute(([
        "str":15+random(6), "cor":9+random(6), "int":5+random(6), "spi":7+random(6),
        "cps":14+random(7), "dex":9+random(6), "con":17+random(6), "wis":10+random(6)
    ]));
    ob->init_statistic(([ "gin":20, "kee":30, "sen":20 ]));
    if (!ob->query("age")) ob->set("age",14+random(4));
    ob->set_default_object(__FILE__);
}
