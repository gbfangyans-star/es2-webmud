/* 追風劍 — ES2 參考資料（es2tips）。肖麗穎埋在雪山古松下，追風劍任務取得。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("追風劍", ({ "storm chaser's sword", "storm chasers sword", "sword" }));
    set_weight(8700);
    init_damage(3, 18, 100, 6, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 5000);
        set("long",
            "「追風劍」，據說是冷梅莊莊主梅影風特意拜託劍甲門傳人為他的獨子\n"
            "梅嵐武所打造的兵刃，可是不知為何，江湖中並沒有人見梅嵐武用過此\n"
            "劍。\n");
        set("apply_weapon/sword", ([
            "damage_vs_ice": 50,
            "damage": 10,
            "attack": 50,
        ]));
    }
    setup();
}
