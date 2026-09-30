/* 生鐵戰甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("生鐵戰甲", ({ "iron armor", "armor" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 45000);
        set("long",
            "一件十分輕便的盔甲不過看起來防禦力不錯。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 25,
        ]));
    }
    setup();
}
