/* 繡花針 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_NEEDLE;

void create()
{
    set_name("繡花針", ({ "embroidery needle", "needle" }));
    set_weight(500);
    init_damage(1, 15, 100, 4, "needle");
    init_damage(1, 15, 100, 4, "secondhand needle");

    if( !clonep() ) {
        set("wield_as", ({ "needle", "secondhand needle" }));
        set("unit", "把");
        set("value", 55000);
        set("long",
            "一支普通的繡花針。\n");
    }
    setup();
}
