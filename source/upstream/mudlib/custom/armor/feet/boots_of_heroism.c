/* 英雄戰靴 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("英雄戰靴", ({ "boots of heroism", "boots" }));
    set_weight(1000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 19000);
        set("long",
            "一雙看起來很氣派的鞋子，鞋背上面還繡了一對老虎。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 50,
            "defense": 25,
        ]));
    }
    setup();
}
