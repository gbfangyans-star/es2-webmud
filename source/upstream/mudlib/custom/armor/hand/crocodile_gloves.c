/* 鱷皮手套 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("\x1b[1;32m鱷皮手套\x1b[m", ({ "crocodile gloves", "gloves" }));
    set_weight(400);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 3000);
        set("long",
            "一雙鱷魚皮製的手套，不但輕巧防護力也是上選，是個很高等的護手。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "defense": 10,
            "damage": 5,
        ]));
    }
    setup();
}
