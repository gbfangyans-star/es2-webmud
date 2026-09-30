/* 蠶絲手套 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("\x1b[1;37m蠶絲手套\x1b[m", ({ "silk gloves", "gloves" }));
    set_weight(200);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 1000);
        set("long",
            "一雙蠶絲編成的手套，可以提供相當程度的保護。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor_vs_ice": 25,
            "unarmed": 10,
        ]));
    }
    setup();
}
