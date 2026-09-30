/* 藤甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("藤甲", ({ "banded armor", "armor" }));
    set_weight(3000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 2000);
        set("long",
            "一件用浸過油的粗籐所編成的護甲，輕便堅固。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 12,
            "dodge": 5,
        ]));
    }
    setup();
}
