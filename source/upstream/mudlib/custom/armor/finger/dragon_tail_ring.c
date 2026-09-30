/* 暴龍尾骨 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;37m暴龍尾骨\x1b[m", ({ "dragon tail", "ring" }));
    set_weight(500);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "片");
        set("value", 100);
        set("long",
            "一片環形的暴龍尾骨，也許可以戴在手指上當戒指用。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 30,
            "con": 1,
            "dex": 1,
            "armor_vs_ice": 50,
        ]));
    }
    setup();
}
