/* 暴龍牙 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("\x1b[1;37m暴龍牙\x1b[m", ({ "dragon dagger", "dagger" }));
    set_weight(5700);
    init_damage(2, 15, 100, 8, "dagger");
    init_damage(2, 15, 100, 8, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 100);
        set("long",
            "一枚暴龍的牙齒，握在手裡可以當匕首用。\n");
        set("apply_weapon/dagger", ([
            "cps": 1,
            "armor": 15,
            "wittiness": 50,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "cps": 1,
            "armor": 15,
            "wittiness": 50,
        ]));
    }
    setup();
}
