/* 冥思指環 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;34m冥思指環\x1b[m", ({ "meditation ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 50000);
        set("long",
            "一枚散發出讓人懮傷的深藍色光芒的奇妙戒指。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "spi": 1,
            "dex": 1,
            "armor": 5,
        ]));
    }
    setup();
}
