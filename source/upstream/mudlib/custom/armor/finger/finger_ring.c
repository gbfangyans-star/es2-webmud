/* 手指虎 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("手指虎", ({ "finger ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 65000);
        set("long",
            "一副精鋼煉鑄而成的手指虎, 其尖銳處發出陣陣的冷光。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "str": 1,
            "attack": 5,
        ]));
    }
    setup();
}
