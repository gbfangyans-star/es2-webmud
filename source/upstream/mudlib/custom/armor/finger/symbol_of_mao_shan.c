/* 茅山信物 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("茅山信物", ({ "symbol of mao-shan", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 80000);
        set("long",
            "一枚滿是銹跡的戒指，鑲嵌在戒指上的玉石不知為甚麼竟然是\n"
            "一把劍的形狀。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "mao-shan sword": 10,
            "wittiness": 15,
        ]));
    }
    setup();
}
