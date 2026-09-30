/* 獸面玉戒 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;37m獸面玉戒\x1b[m", ({ "beast ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 5000);
        set("long",
            "用整塊白玉雕成的戒指，上面刻有不知名野獸的臉。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "attack": 10,
            "intimidate": 10,
        ]));
    }
    setup();
}
