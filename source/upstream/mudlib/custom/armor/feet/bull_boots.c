/* 蠻牛靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("蠻牛靴", ({ "bull boots", "boots" }));
    set_weight(1000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 8000);
        set("long",
            "蠻牛靴用野牛皮製成，兼顧耐穿與輕便兩個優點。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor_vs_ice": 25,
            "str": 1,
        ]));
    }
    setup();
}
