/* 英雄護手 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("英雄護手", ({ "gloves of heroism", "gloves" }));
    set_weight(800);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 15000);
        set("long",
            "十分沉重的黃銅護手，上面雕刻著一些高雅的條紋。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor": 30,
            "defense": 30,
        ]));
    }
    setup();
}
