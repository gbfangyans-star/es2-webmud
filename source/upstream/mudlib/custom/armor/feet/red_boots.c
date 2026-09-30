/* 啖紅裐雲靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("啖紅裐雲靴", ({ "red boots", "boots" }));
    set_weight(500);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 10000);
        set("long",
            "一雙血紅色的斕裯布靴, 手工顯得非常精巧。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "dodge": 8,
            "armor": 4,
        ]));
    }
    setup();
}
