/* 風神之羽 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;36m風神之羽\x1b[m", ({ "storm-lord's feather", "sword" }));
    set_weight(21200);
    init_damage(4, 19, 160, 5, "twohanded sword");

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 50000);
        set("long",
            "風神「大鵬」的額上之羽，形若無物卻重達千斤，迎風揮舞悄然無\n"
            "聲。道道清風附於劍刃，將劍身藏於在旋風之中。\n");
        set("apply_weapon/twohanded sword", ([
            "cps": 4,
            "defense": 40,
            "armor_vs_wind": 100,
            "taoism-storm": 30,
        ]));
    }
    setup();
}
