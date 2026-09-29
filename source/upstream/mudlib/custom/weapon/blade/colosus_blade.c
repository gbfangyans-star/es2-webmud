/* 巨刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("巨刀", ({ "colosus blade", "blade" }));
    set_weight(18800);
    init_damage(3, 21, 90, 6, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 50000);
        set("long",
            "一把約六尺長的巨刀﹐份量奇重，需要相當的膂力才能揮舞這種武器。\n");
    }
    setup();
}
