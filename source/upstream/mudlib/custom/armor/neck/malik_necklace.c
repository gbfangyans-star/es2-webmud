/* 巫首項鍊 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("巫首項鍊", ({ "malik necklace", "necklace" }));
    set_weight(200);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 13000);
        set("long",
            "一串色澤有些發暗的楠木珠子。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "spi": 2,
            "int": 2,
            "wis": 2,
        ]));
    }
    setup();
}
