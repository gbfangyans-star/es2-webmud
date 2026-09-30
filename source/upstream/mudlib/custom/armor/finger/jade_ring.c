/* 鑲玉指環 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;32m鑲玉指環\x1b[m", ({ "jade ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 65000);
        set("long",
            "一個玄鐵所造的指環，上面鑲著一塊綠玉，映著日光隱約可見到綠玉內出\n"
            "現淩雲二字。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "cor": 1,
            "cps": 1,
        ]));
    }
    setup();
}
