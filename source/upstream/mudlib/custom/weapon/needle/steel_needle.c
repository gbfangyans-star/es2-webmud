/* 鋼針 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_NEEDLE;

void create()
{
    set_name("鋼針", ({ "steel needle", "needle" }));
    set_weight(500);
    init_damage(2, 5, 80, 2, "needle");
    init_damage(2, 5, 80, 2, "secondhand needle");

    if( !clonep() ) {
        set("wield_as", ({ "needle", "secondhand needle" }));
        set("unit", "把");
        set("value", 300);
        set("long",
            "一支鋼製灸針，長約一掌，是江湖郎中常用的醫療器具。\n");
    }
    setup();
}
