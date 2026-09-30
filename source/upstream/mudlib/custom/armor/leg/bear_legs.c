/* 白熊護腿 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_LEG_EQ;

void create()
{
    set_name("\x1b[1;37m白熊護腿\x1b[m", ({ "bear legs", "legs" }));
    set_weight(600);
    setup_leg_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 1000);
        set("long",
            "一雙由千年白熊的皮所製作而成的護腿，此護腿整雙毛茸茸的。\n");
        set("wear_as", "leg_eq");
        set("apply_armor/leg_eq", ([
            "armor": 5,
            "armor_vs_ice": 5,
        ]));
    }
    setup();
}
