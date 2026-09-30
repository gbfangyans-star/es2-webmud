/* 赤龍鱗 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("赤龍鱗", ({ "brimstony armor", "armor" }));
    set_weight(5000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 25000);
        set("long",
            "這是一件用赤龍的龍鱗做成的盔甲﹐不僅具有不同凡響的防禦力﹐\n"
            "還具有一定的法術防禦力。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor_vs_wind": 20,
            "armor": 30,
            "armor_vs_fire": 20,
            "str": 2,
        ]));
    }
    setup();
}
