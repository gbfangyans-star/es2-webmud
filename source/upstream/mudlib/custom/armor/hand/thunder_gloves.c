/* 狂雷手套 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("狂雷手套", ({ "thunder gloves", "gloves" }));
    set_weight(400);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 10000);
        set("long",
            "一雙藍色手套，外層硬度奇佳。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "parry": 5,
            "twohanded blade": 10,
            "armor": 5,
        ]));
    }
    setup();
}
