/* 靈惑之尾 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("靈惑之尾", ({ "dragon tail", "tail" }));
    set_weight(1000);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 100000);
        set("long",
            "這條尾巴看似豹尾卻又長滿鱗片，頗為沉重。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "armor_vs_wind": 50,
            "wittiness": 25,
            "spi": 2,
            "armor_vs_ice": 50,
        ]));
    }
    setup();
}
