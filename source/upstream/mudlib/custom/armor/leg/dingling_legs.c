/* 釘靈腿護 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_LEG_EQ;

// 種族裝備：只有釘靈族能穿戴（使用者指定）。
varargs int wear(string on_part)
{
    object owner = environment();

    if( objectp(owner) && owner->query_race() != "dingling" )
        return notify_fail("只有釘靈族才能穿戴這樣東西。\n");
    return ::wear(on_part);
}

void create()
{
    set_name("釘靈腿護", ({ "dingling legs", "legs" }));
    set_weight(1000);
    setup_leg_eq();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 11000);
        set("long",
            "一套非常獨特的腿護，不過看起來好像更適合給戰馬佩戴。\n");
        set("wear_as", "leg_eq");
        set("apply_armor/leg_eq", ([
            "armor": 50,
            "move": 50,
            "intimidate": 50,
        ]));
    }
    setup();
}
