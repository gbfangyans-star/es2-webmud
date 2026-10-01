/* 疾步快靴 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("疾步快靴", ({ "runner's boots", "runners boots", "boots" }));
    set_weight(1000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 76000);
        set("long",
            "一雙內襯鬼獫之毛外縫紉鬼獫之皮的罕見靴子。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 25,
            "armor_vs_ice": 100,
            "dex": 3,
        ]));
    }
    setup();
}
