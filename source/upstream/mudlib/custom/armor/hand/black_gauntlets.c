/* 黑鐵護手 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("黑鐵護手", ({ "black gauntlets", "gauntlets" }));
    set_weight(800);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 25000);
        set("long",
            "一雙相當精緻的藍色護手, 上面繡著金黃色的鳳凰圖案。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "intimidate": 10,
            "str": 1,
        ]));
    }
    setup();
}
