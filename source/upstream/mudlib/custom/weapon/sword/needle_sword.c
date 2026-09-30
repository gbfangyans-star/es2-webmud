/* 雙鬢鋏 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;37m雙鬢鋏\x1b[m", ({ "needle sword", "sword" }));
    set_weight(2500);
    init_damage(2, 5, 50, 1, "sword");
    init_damage(2, 5, 50, 1, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 40000);
        set("long",
            "一把雪白的短劍，劍柄留有兩條相當長的白色絲帶。\n");
        set("apply_weapon/sword", ([
            "damage": 5,
            "cor": 1,
        ]));
        set("apply_weapon/secondhand sword", ([
            "damage": 5,
            "cor": 1,
        ]));
    }
    setup();
}
