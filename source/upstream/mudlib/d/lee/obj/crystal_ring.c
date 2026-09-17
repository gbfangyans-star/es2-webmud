// /d/lee/obj/crystal_ring.c
// NEW（李家村復原版新增道具，非原始 ES2 資料，由專案成員指定數值）

#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("水晶戒指", ({ "crystal ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 100000);
        set("long", "一枚透明剔透的水晶戒指，戴在指間隱隱流轉著清靈之氣。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "spi": 1,
        ]));
    }

    setup();
}
