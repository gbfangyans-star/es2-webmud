/* 淨身戒 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("淨身戒", ({ "clear ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 50000);
        set("long",
            "此乃淨衣道神教教主隨身之戒。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 5,
            "cps": 2,
            "wis": 2,
        ]));
    }
    setup();
}
