/* 英雄護腿 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_LEG_EQ;

void create()
{
    set_name("英雄護腿", ({ "legs of heroism", "legs" }));
    set_weight(1000);
    setup_leg_eq();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 25000);
        set("long",
            "一套用黃銅打製的護腿，內嵌著一層柔軟的獸皮。\n");
        set("wear_as", "leg_eq");
        set("apply_armor/leg_eq", ([
            "wittiness": 30,
            "armor": 30,
            "defense": 30,
        ]));
    }
    setup();
}
