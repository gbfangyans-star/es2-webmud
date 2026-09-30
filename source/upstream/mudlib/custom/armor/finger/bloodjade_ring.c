/* 血玉戒指 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;31m血玉戒指\x1b[m", ({ "bloodjade ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 50000);
        set("long",
            "這隻戒指是用產量稀少的血玉製成的，通體赤紅。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "cor": 2,
        ]));
    }
    setup();
}
