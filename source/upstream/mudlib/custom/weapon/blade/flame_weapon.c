/* 妄焱兵絕 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("妄焱兵絕", ({ "flame weapon", "blade" }));
    set_weight(4000);
    init_damage(2, 13, 80, 0, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 25000);
        set("long",
            "一把鏽黑的兵器，刃身上隱隱有火熾的痕跡。\n");
    }
    setup();
}
