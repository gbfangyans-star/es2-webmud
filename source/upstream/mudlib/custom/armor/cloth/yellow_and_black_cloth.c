/* 虎紋黃衣 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("虎紋黃衣", ({ "yellow and black cloth", "cloth" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 10000);
        set("long",
            "這件衣服用黃色的生絲織成，間有烏金絲組成的虎紋。看起來美\n"
            "觀，也提供了不錯的防護力。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "str": 1,
            "armor": 8,
        ]));
    }
    setup();
}
