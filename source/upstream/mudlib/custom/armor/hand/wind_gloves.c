/* 疾風套手 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("疾風套手", ({ "wind gloves", "gloves" }));
    set_weight(400);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 3000);
        set("long",
            "一雙輕薄手套, 彈性奇佳, 內層似有軔性金屬, 上面繡有一些奇特符號.\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor_vs_wind": 25,
            "armor": 5,
        ]));
    }
    setup();
}
