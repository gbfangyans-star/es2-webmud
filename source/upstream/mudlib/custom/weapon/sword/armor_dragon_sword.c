/* 玄武『青龍』劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;33m玄武\x1b[1;32m『青龍』\x1b[1;33m劍\x1b[m", ({ "armor-dragon sword", "sword" }));
    set_weight(7200);
    init_damage(3, 15, 100, 4, "sword");
    init_damage(3, 15, 100, 4, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 5000);
        set("long",
            "一把散發出幽暗的金光的短劍, 劍身是短而寬﹐形如玄武。\n"
            "劍柄處盤繞一條青龍﹐頗為典雅。\n");
    }
    setup();
}
