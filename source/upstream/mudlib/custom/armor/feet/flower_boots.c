/* 小繡花鞋 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("小繡花鞋", ({ "flower boots", "boots" }));
    set_weight(500);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 2000);
        set("long",
            "這是一雙看起來非常秀氣的繡花小鞋, 很輕巧的樣子。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 2,
        ]));
    }
    setup();
}
