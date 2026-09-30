/* 冷玉寶劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;37m冷玉寶劍\x1b[m", ({ "jade sword", "sword" }));
    set_weight(3300);
    init_damage(2, 10, 50, 1, "sword");
    init_damage(2, 5, 50, 1, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 60000);
        set("long",
            "一柄用上好的白玉製成的寶劍。\n");
        set("apply_weapon/sword", ([
            "spi": 1,
            "dex": 1,
        ]));
        set("apply_weapon/secondhand sword", ([
            "spi": 1,
            "dex": 1,
        ]));
    }
    setup();
}
