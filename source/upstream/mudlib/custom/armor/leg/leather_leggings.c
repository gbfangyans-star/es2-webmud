/* 牛皮綁腿 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_LEG_EQ;

void create()
{
    set_name("牛皮綁腿", ({ "leather leggings", "leggings" }));
    set_weight(600);
    setup_leg_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 500);
        set("long",
            "一套牛皮製成的護腿裝備, 是黑風寨土匪自製的防具。\n");
        set("wear_as", "leg_eq");
        set("apply_armor/leg_eq", ([
            "armor": 5,
            "sneak": 5,
        ]));
    }
    setup();
}
