/* 寒蟾指環 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;32m寒蟾指環\x1b[m", ({ "frost frog ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 20000);
        set("long",
            "一枚鑲入了寒蟾冰膽的玉戒指﹐看起來晶瑩透明鮮翠欲滴。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor_vs_ice": 20,
            "wis": 2,
            "spells": 10,
        ]));
    }
    setup();
}
