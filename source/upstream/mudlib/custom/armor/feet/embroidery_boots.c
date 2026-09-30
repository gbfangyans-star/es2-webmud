/* 繡花鞋 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("繡花鞋", ({ "embroidery boots", "boots" }));
    set_weight(500);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 3000);
        set("long",
            "一雙作工精緻的紅色繡花鞋，鞋面上繡著一朵藍色牡丹，前端還有一顆白色小絨球。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 3,
        ]));
    }
    setup();
}
