/* 綠玉頂戴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("\x1b[1;32m綠玉頂戴\x1b[m", ({ "jade hat", "hat" }));
    set_weight(300);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 30000);
        set("long",
            "白絲製成的官帽，上頭還鑲著一塊翠綠色的玉。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "spi": 1,
            "mysticism": 5,
        ]));
    }
    setup();
}
