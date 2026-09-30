/* 青鋼短劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("青鋼短劍", ({ "iron sword", "sword" }));
    set_weight(5500);
    init_damage(2, 18, 90, 1, "sword");
    init_damage(2, 9, 90, 1, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 95000);
        set("long",
            "一把用青鋼製成的短劍, 劍頭上沾著些許血跡。\n");
    }
    setup();
}
