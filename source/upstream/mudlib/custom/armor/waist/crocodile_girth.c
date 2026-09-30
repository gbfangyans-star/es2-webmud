/* 鱷神束帶 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("\x1b[1;32m鱷神束帶\x1b[m", ({ "crocodile girth", "girth" }));
    set_weight(800);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 10000);
        set("long",
            "這是一條用巨鱷王鱷皮製成的腰帶，由觸摸它時那種觸感告訴你，這\n"
            "件鱷皮必然非常之堅厚，當時要斬殺這隻鱷魚相信必定經過一番苦戰\n"
            "腰帶邊緣用鱷魚的牙齒做裝飾，看著食指般長度的鱷齒，不由得讓你\n"
            "想像起這頭奇獸的姿態。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "cor": 1,
            "str": 1,
        ]));
    }
    setup();
}
