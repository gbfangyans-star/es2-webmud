/* 道袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("道袍", ({ "robe" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 30000);
        set("long",
            "一件質料很好的青色道袍 ,穿在身上有一些防護力。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor_vs_ice": 10,
            "dodge": 3,
            "armor": 2,
        ]));
    }
    setup();
}
