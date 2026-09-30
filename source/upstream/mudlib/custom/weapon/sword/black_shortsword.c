/* 黑色短劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("黑色短劍", ({ "black shortsword", "sword" }));
    set_weight(3200);
    init_damage(2, 10, 50, 0, "sword");
    init_damage(2, 5, 50, 0, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 45000);
        set("long",
            "一把由玄鐵打造而成的短劍, 劍身還刻了幾個小字.\n");
        set("apply_weapon/sword", ([
            "spi": 1,
            "attack": 12,
        ]));
        set("apply_weapon/secondhand sword", ([
            "spi": 1,
            "attack": 12,
        ]));
    }
    setup();
}
