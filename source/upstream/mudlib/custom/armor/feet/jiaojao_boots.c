/* 焦僥靴 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

// 種族裝備：只有焦僥族能穿戴（使用者指定）。
varargs int wear(string on_part)
{
    object owner = environment();

    if( objectp(owner) && owner->query_race() != "jiaojao" )
        return notify_fail("只有焦僥族才能穿戴這樣東西。\n");
    return ::wear(on_part);
}

void create()
{
    set_name("焦僥靴", ({ "jiaojao's boots", "jiaojao boots", "boots" }));
    set_weight(500);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 30000);
        set("long",
            "一雙小巧精緻的靴子，一般人是穿不上的。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 50,
            "move": 100,
            "awarness": 100,
        ]));
    }
    setup();
}
