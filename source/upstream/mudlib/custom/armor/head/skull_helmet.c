/* 獸骨盔 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("\x1b[1;37m獸骨盔\x1b[m", ({ "skull helmet", "helmet" }));
    set_weight(800);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 50000);
        set("long",
            "一頂用雍和頭骨做成的頭盔，上面還鑲著一枚黑色的龍珠。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor_vs_wind": 50,
            "armor_vs_ice": 50,
            "armor": 30,
        ]));
    }
    setup();
}
