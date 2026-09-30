/* 青金指環 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;34m青金指環\x1b[m", ({ "lapis ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 90000);
        set("long",
            "一枚做工十分細緻的金戒指，戒指上還鑲嵌了一粒黑黑的珠子。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "spi": 1,
            "int": 2,
        ]));
    }
    setup();
}
