/* 邪骨指環 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("邪骨指環", ({ "symbol of dao", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 90000);
        set("long",
            "一枚骷髏形的戒指，戒指上深深的刻著一個邪字，不知道是\n"
            "哪一派的信物。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "wittiness": 25,
            "seven_blade": 5,
        ]));
    }
    setup();
}
