/* 針織手套 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("針織手套", ({ "embroidery gloves", "gloves" }));
    set_weight(200);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 5000);
        set("long",
            "一雙淺藍色帶白色條紋的針織手套，戴在手上感覺非常保暖喔。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor": 2,
        ]));
    }
    setup();
}
