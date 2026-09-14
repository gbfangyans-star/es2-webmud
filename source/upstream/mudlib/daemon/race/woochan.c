/* CUSTOM A-H RACE: 無腸 (woochan). User-supplied race specification. */
#define BASE_WEIGHT 40000
#include <race.h>
#include <statistic.h>
inherit HUMANOID;

private void create() {
    ::create(); seteuid(getuid());
    set("karma",5); set("civilized",1); set("commoner_score_base",100);
    set("class_level_cap", ([
        "commoner":50, "fighter":50, "taoist":60, "alchemist":60,
        "soldier":50, "scholar":60, "monk":65, "thief":50
    ]));
    DAEMON_D->register_race_daemon("woochan");
}
void setup(object ob) {
    ::setup(ob); ob->set_default_object(__FILE__);
    if (!ob->query_weight()) ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str",1)-13)*5000);
    ob->add_temp("apply/armor",5);
    ob->add_temp("apply/wittiness",25);
    // 無腸不需要食物。先停止既有食物消耗，再將飽食度固定為 0/0。
    // 飲水仍照 canonical 規則消耗。
    ob->set_stat_regenerate("food", TYPE_STATIC);
    ob->set_stat_current("food", 0);
    ob->set_stat_effective("food", 0);
    ob->set_stat_maximum("food", 0);
}
void initialize(object ob) {
    ::initialize(ob);
    ob->init_attribute(([
        "str":10+random(6), "cor":10+random(6), "int":15+random(5), "spi":15+random(5),
        "cps":12+random(7), "dex":15+random(6), "con":10+random(6), "wis":15+random(8)
    ]));
    ob->init_statistic(([ "gin":30, "kee":20, "sen":60 ]));
    if (!ob->query("age")) ob->set("age",14+random(4));
    ob->set_default_object(__FILE__);
}
