/* 青雲戰靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("\x1b[1;32m青雲戰靴\x1b[m", ({ "green boots of soldier", "boots" }));
    set_weight(2000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 25000);
        set("long",
            "一雙亮綠色的的鋼網長靴．是焱硝村軍旅的特殊裝備,由當地的特殊鐵礦製成\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "defense": 10,
            "cor": 1,
            "armor": 5,
        ]));
    }
    setup();
}
