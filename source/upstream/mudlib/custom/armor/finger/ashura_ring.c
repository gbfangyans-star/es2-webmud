/* 修羅戒 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;31m修羅戒\x1b[m", ({ "ashura ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 80000);
        set("long",
            "一枚血紅色的戒指，光是看著它鮮紅色的表面，就會令人心跳加速，有\n"
            "種想一嚐鮮血味道的衝動。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "wittiness": -20,
            "cor": 1,
            "attack": 10,
        ]));
    }
    setup();
}
