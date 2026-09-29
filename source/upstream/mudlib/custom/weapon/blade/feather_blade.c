/* 翠羽刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;32m翠羽刀\x1b[m", ({ "feather blade", "blade" }));
    set_weight(9200);
    init_damage(3, 20, 110, 4, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 75000);
        set("long",
            "此刀通身翠綠，如同孔雀的羽毛一樣美麗。輕輕揮舞，猶如\n"
            "一隻孔雀在風中獨舞，美得讓人心碎。江湖之中勝傳此刀內\n"
            "藏有火神鳳凰的羽毛。\n");
        set("apply_weapon/blade", ([
            "armor_vs_wind": 65,
            "intimidate": 25,
            "seven_blade": 5,
            "attack": 15,
        ]));
    }
    setup();
}
