/* 萬福寶玉 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("\x1b[1;32m萬福寶玉\x1b[m", ({ "blessed jade", "jade" }));
    set_weight(800);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 10000);
        set("long",
            "這是一條用數十塊雕滿了祈福的符咒的上等玉石串連而成的腰帶。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "spells": 10,
            "spi": 1,
            "armor": 10,
        ]));
    }
    setup();
}
