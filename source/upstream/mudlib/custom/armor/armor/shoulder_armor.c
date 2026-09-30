/* 藍鋼肩甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;34m藍鋼肩甲\x1b[m", ({ "shoulder armor", "armor" }));
    set_weight(2000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 9500);
        set("long",
            "一件發著暗藍光芒的肩甲，穿上這件甲胄可以保護左肩以及重要的\n"
            "心臟部位，肩甲下方還有兩條皮帶可緊緊的將肩甲固定在肩上，是\n"
            "一種極簡便又實用的戰甲。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 10,
        ]));
    }
    setup();
}
