/* CUSTOM A-H RACE: 刑天 (headless). User-supplied race specification. */
#define BASE_WEIGHT 40000
#include <race.h>
inherit HUMANOID;

private void create() {
    ::create(); seteuid(getuid());
    set("karma", 25); set("civilized", 1); set("commoner_score_base", 100);
    set("class_level_cap", ([
        "commoner":50, "fighter":65, "taoist":50, "alchemist":50,
        "soldier":70, "scholar":50, "monk":1, "thief":50
    ]));
    // 天生戰士，沒有頭部、頸部可供攻擊或裝飾。
    set("limbs", ({
        "胸口", "後心", "左肩", "右肩", "左臂",
        "右臂", "左手", "右手", "腰間", "小腹", "左腿", "右腿",
        "左腳", "右腳"
    }));
    DAEMON_D->register_race_daemon("headless");
}
void setup(object ob) {
    ::setup(ob); ob->set_default_object(__FILE__);
    if (!ob->query_weight()) ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str",1)-13)*5000);
    ob->add_temp("apply/attack", 50);
    ob->add_temp("apply/defense", 100);
    ob->add_temp("apply/armor", 100);
    ob->add_temp("apply/move", 50);
}
void initialize(object ob) {
    ::initialize(ob);
    ob->init_attribute(([
        "str":25+random(6), "cor":15+random(6), "int":6+random(4), "spi":12+random(5),
        "cps":12+random(5), "dex":18+random(7), "con":24+random(5), "wis":14+random(5)
    ]));
    ob->init_statistic(([ "gin":80, "kee":100, "sen":30 ]));
    if (!ob->query("age")) ob->set("age",14+random(4));
    ob->set_default_object(__FILE__);
}

// 無首、無頸：不能穿盔甲、衣服、頭盔、項鍊，其餘護具（手部、腳部、腿部、
// 腰部、戒指）不受影響，交給父類別原本的檢查（已穿戴同類/種族護具白名單）。
int valid_wear(object me, object ob, string part) {
    if (member_array(part, ({ "armor", "cloth", "head_eq", "neck_eq" })) != -1)
        return notify_fail("刑天沒有頭部與軀幹，無法穿戴這種護具。\n");
    return ::valid_wear(me, ob, part);
}
