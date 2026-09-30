/* 軟皮靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("軟皮靴", ({ "boots" }));
    set_weight(1000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 500);
        set("long",
            "一雙鹿皮軟靴，似乎是女子式樣。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 1,
            "dodge": 5,
        ]));
    }
    setup();
}
