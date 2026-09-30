/* 舞璃戒指 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;37m舞璃戒指\x1b[m", ({ "wuzin ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 60000);
        set("long",
            "一枚像雞蛋般大小的寶石鑲在戒指上,寶石上有著很多的\n"
            "細小紋路, 不知道有什麼功能。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "cps": 1,
        ]));
    }
    setup();
}
