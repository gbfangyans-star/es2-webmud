/* 鱷皮靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("\x1b[1;32m鱷皮靴\x1b[m", ({ "crocodile boots", "boots" }));
    set_weight(1000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 3000);
        set("long",
            "一雙鱷魚皮製的長靴，又輕又軟，是雙不錯的的靴子。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "dodge": 10,
            "dex": 2,
        ]));
    }
    setup();
}
