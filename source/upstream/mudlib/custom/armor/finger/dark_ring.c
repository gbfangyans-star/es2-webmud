/* 闇之魔戒 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;30m闇之魔戒\x1b[m", ({ "dark ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 130000);
        set("long",
            "一枚通體暗黑的戒指，不停的散發出一種奇妙的光芒，讓人覺得有些頭暈。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor_vs_fire": 50,
            "armor_vs_lightning": 50,
            "stealing": 15,
        ]));
    }
    setup();
}
