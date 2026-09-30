/* 封龍鎖 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;31m封龍鎖\x1b[m", ({ "sealed-dragon ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 100000);
        set("long",
            "一枚龍形的戒指﹐龍的口裡含著一粒黑黑的小珠子。令人驚異\n"
            "的是﹐龍目中似乎流出兩股龍血﹐染滿了整個戒指。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "force": 10,
            "armor": 10,
            "intimidate": 10,
        ]));
    }
    setup();
}
