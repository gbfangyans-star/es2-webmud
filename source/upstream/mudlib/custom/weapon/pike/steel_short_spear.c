/* 精鋼短槍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("精鋼短槍", ({ "steel short spear", "pike" }));
    set_weight(4800);
    init_damage(3, 10, 60, 2, "pike");
    init_damage(3, 10, 30, 2, "secondhand pike");

    if( !clonep() ) {
        set("wield_as", ({ "pike", "secondhand pike" }));
        set("unit", "把");
        set("value", 75000);
        set("long",
            "一把約五尺長的短槍﹐看來有不錯的攻擊力。\n");
        set("apply_weapon/pike", ([
            "damage": 3,
        ]));
        set("apply_weapon/secondhand pike", ([
            "damage": 3,
        ]));
    }
    setup();
}
