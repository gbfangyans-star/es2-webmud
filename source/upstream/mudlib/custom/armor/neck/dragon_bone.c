/* 靈骨 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("靈骨", ({ "dragon bone", "bone" }));
    set_weight(300);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "顆");
        set("value", 2000);
        set("long",
            "一顆只有少數老年的龍才會長的骨頭﹐據說擁有強大的法力。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "spells": 10,
            "taoism-storm": 5,
            "taoism-thunder": 5,
            "taoism-freeze": 5,
            "taoism-fire": 5,
        ]));
    }
    setup();
}
