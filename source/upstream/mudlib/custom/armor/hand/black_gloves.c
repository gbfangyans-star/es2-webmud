/* 黑手套 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("黑手套", ({ "black gloves", "gloves" }));
    set_weight(200);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 15000);
        set("long",
            "一雙全部由黑色細絲做成的手套，非常適合夜間暗殺時穿戴。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "secondhand dagger": 5,
            "dagger": 5,
            "armor": 1,
        ]));
    }
    setup();
}
