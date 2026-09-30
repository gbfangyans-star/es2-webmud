/* 豹耳襄王戒 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;33m豹耳襄王戒\x1b[m", ({ "leopard ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 85000);
        set("long",
            "一只樣式奇特，望之若豹耳的戒指，據聞這是古時將王以箭射穿石\n"
            "豹，所得之金屬鍛鍊而成的戒指。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "wittiness": 30,
            "dex": 1,
        ]));
    }
    setup();
}
