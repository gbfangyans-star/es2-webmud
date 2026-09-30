/* 龍戒 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;33m龍戒\x1b[m", ({ "dragon-soul ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 100000);
        set("long",
            "一枚做工精細的黃金戒指。整枚戒指是一條逼真的天龍﹐龍身纏繞而昇﹐龍口處\n"
            "含著一顆散發出金色光芒的神奇寶石。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "str": 2,
            "wittiness": 25,
        ]));
    }
    setup();
}
