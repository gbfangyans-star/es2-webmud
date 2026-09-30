/* 鐵丐靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("鐵丐靴", ({ "iron boots", "boots" }));
    set_weight(2000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 30000);
        set("long",
            "一雙白鐵打製成的靴子, 看起來挺笨重的樣子。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 8,
            "force": 3,
            "parry": 3,
            "dodge": -3,
        ]));
    }
    setup();
}
