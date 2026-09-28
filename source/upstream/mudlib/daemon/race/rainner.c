/* CUSTOM RACE: 雨師妾 (rainner). Original race data 2006/09/15. */
#define BASE_WEIGHT 40000
#define SNAKE_OB "/custom/race/obj/rainner_snake"
#include <ansi.h>
#include <race.h>
inherit HUMANOID;

// 一生最多五條小蛇，每次升級有 1/2 機會得到一條還沒有的。
private string *snake_colors = ({ "white", "black", "green", "red", "yellow" });

private void create() {
    ::create(); seteuid(getuid());
    set("karma", 25); set("civilized", 1); set("commoner_score_base", 100);
    set("class_level_cap", ([
        "commoner":1, "fighter":50, "taoist":55, "alchemist":55,
        "soldier":50, "scholar":55, "monk":65, "thief":60
    ]));
    DAEMON_D->register_race_daemon("rainner");
}

// 蛇的經驗記在玩家身上（rainner/snake/<顏色>），蛇物件每次登入依記錄重建，
// 所以登出不會掉、登入一定在身上。
object find_snake(object ob, string color) {
    object inv;
    foreach (inv in all_inventory(ob))
        if (inv->query("rainner_snake") == color) return inv;
    return 0;
}

object give_snake(object ob, string color) {
    object snake = find_snake(ob, color);
    if (!snake) {
        snake = new(SNAKE_OB);
        snake->set_owner(ob, color);
        if (!snake->move(ob)) { destruct(snake); return 0; }
    }
    // 死後復活會清掉暫存資料，已不在身上生效的裝備狀態要先清掉再重新穿上。
    if (snake->query("equipped") && ob->query_temp(snake->query("equipped")) != snake)
        snake->delete("equipped");
    snake->refresh();
    if (!snake->query("equipped") && ob->query("rainner/worn/" + color))
        snake->wear();
    return snake;
}

void setup(object ob) {
    mapping snakes;
    string color;

    ::setup(ob); ob->set_default_object(__FILE__);
    if (!ob->query_weight()) ob->set_weight(BASE_WEIGHT + ((int)ob->query_attr("str",1)-13)*5000);
    ob->add_temp("apply/armor", 5);
    ob->add_temp("apply/magic", 10);     // 法力值 +10 = 法術技巧額外附加

    if (userp(ob) && mapp(snakes = ob->query("rainner/snake")))
        foreach (color in keys(snakes)) give_snake(ob, color);
}

void initialize(object ob) {
    ::initialize(ob);
    ob->init_attribute(([
        "str":6+random(4), "cor":6+random(4), "int":17+random(6), "spi":18+random(7),
        "cps":15+random(6), "dex":10+random(4), "con":10+random(4), "wis":20+random(9)
    ]));
    ob->init_statistic(([ "gin":40, "kee":30, "sen":70 ]));
    if (!ob->query("age")) ob->set("age", 14+random(4));
    ob->set_default_object(__FILE__);
}

void advance_level(object ob) {
    string *left = ({}), color;
    mapping snakes;
    object snake;

    ::advance_level(ob);
    if (!userp(ob) || random(2)) return;

    snakes = ob->query("rainner/snake");
    foreach (color in snake_colors)
        if (!mapp(snakes) || undefinedp(snakes[color])) left += ({ color });
    if (!sizeof(left)) return;

    color = left[random(sizeof(left))];
    ob->set("rainner/snake/" + color, 0);
    ob->set("rainner/worn/" + color, 1);
    if (snake = give_snake(ob, color))
        tell_object(ob, HIG "一條小小的" + snake->name() + HIG
            "從你的袖口鑽了出來，親暱地纏上你的身體。\n" NOR);
}
