/* 參龍『麒麟』劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;33m參龍\x1b[1;31m『麒麟』\x1b[1;33m劍\x1b[m", ({ "pure-dragon sword", "sword" }));
    set_weight(7900);
    init_damage(3, 16, 120, 6, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 10000);
        set("long",
            "一把泛著淡紅色血光的長劍, 劍身是猶如一條『金龍』﹐華麗無比﹐\n"
            "劍柄為一『麒麟』頭﹐麒麟眼是紅光的來源。\n");
        set("apply_weapon/sword", ([
            "damage": 10,
            "cor": 2,
        ]));
    }
    setup();
}
