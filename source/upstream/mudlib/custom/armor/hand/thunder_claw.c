/* 雷熊爪 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("雷熊爪", ({ "thunder claw", "claw" }));
    set_weight(800);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 5000);
        set("long",
            "一雙用奇獸雷熊的前爪製成的護手，隱隱的散發著道道雷光。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor_vs_lightning": 50,
            "defense": 25,
        ]));
    }
    setup();
}
