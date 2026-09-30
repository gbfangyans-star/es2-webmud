/* 短靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("短靴", ({ "buskins" }));
    set_weight(500);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 5000);
        set("long",
            "一雙短統布靴﹐有些破舊了﹐不過還能穿。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 1,
        ]));
    }
    setup();
}
