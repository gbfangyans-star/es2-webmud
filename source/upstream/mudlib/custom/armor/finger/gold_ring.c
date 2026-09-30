/* 黃金戒 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;33m黃金戒\x1b[m", ({ "gold ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 70000);
        set("long",
            "一只完全以黃金打造的戒指，此戒的內環可以看見清楚的「風」的字樣\n"
            "，其外觀是以一不規則的紋路所圍成的。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 5,
            "secondhand blade": 5,
        ]));
    }
    setup();
}
