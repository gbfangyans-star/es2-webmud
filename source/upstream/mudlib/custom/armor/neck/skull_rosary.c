/* 白骨念珠 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("白骨念珠", ({ "skull rosary", "rosary" }));
    set_weight(800);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 30000);
        set("long",
            "一串用人的頭骨串成的念珠 ...\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "armor": 25,
            "attack": 25,
        ]));
    }
    setup();
}
