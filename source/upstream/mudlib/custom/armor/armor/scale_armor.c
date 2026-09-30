/* 鐵披甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("鐵披甲", ({ "scale armor", "armor" }));
    set_weight(8000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 9000);
        set("long",
            "一套用圓形鐵片釘在鎖子甲上，用來提高防護力的鐵披戰甲，因為鐵片\n"
            "的重量很重，因此這種鎧甲只做半身，俗稱「鐵背心」。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 10,
        ]));
    }
    setup();
}
