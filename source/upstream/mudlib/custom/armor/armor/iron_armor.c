/* 鐵戰甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;33m鐵戰甲\x1b[m", ({ "iron armor", "armor" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 50000);
        set("long",
            "一件鐵甲, 是做來打仗的時候穿的,  可以提供相當嚴密的防護,\n"
            "但是相當笨重。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 20,
        ]));
    }
    setup();
}
