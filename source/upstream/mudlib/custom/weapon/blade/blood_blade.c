/* 靈刀祭血 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;31m靈刀祭血\x1b[m", ({ "blood blade", "blade" }));
    set_weight(6100);
    init_damage(3, 12, 90, 5, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 95000);
        set("long",
            "一把血紅的單刀，刀身所用的材質很奇特，刀輕質硬，色呈紅色半透明。\n");
        set("apply_weapon/blade", ([
            "cps": 1,
            "seven_blade": 10,
        ]));
    }
    setup();
}
