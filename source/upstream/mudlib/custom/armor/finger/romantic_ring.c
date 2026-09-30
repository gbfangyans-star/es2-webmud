/* 相思環 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("相思環", ({ "romantic ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 70000);
        set("long",
            "常常被多情之人送給心上人以示相思之苦的金戒指。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "dex": 2,
        ]));
    }
    setup();
}
