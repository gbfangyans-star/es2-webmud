/* 流雲鐵靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("流雲鐵靴", ({ "flycloud boots", "boots" }));
    set_weight(2000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 3500);
        set("long",
            "這是武林中比較不常見的厚重靴子, 似乎和它的名稱不符。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 5,
            "parry": 5,
        ]));
    }
    setup();
}
