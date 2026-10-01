/* 歸心似劍 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("歸心似劍", ({ "loving sword", "sword" }));
    set_weight(3300);
    init_damage(2, 10, 50, 1, "sword");
    init_damage(2, 10, 50, 1, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 95000);
        set("long",
            "一柄看起來還算鋒利，但是雕琢著鴛鴦的短劍，貌似定情之物 ...\n");
        set("apply_weapon/sword", ([
            "attack": 30,
            "damage": 5,
        ]));
        set("apply_weapon/secondhand sword", ([
            "attack": 30,
            "damage": 5,
        ]));
    }
    setup();
}
