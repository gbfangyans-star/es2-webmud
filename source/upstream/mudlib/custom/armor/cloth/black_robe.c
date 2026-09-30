/* 黑袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("黑袍", ({ "black robe", "robe" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 25000);
        set("long",
            "一件用不知名布料縫製而成的黑色布袍，摸起來有些扎手。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 2,
            "armor_vs_fire": 10,
            "awarness": 20,
        ]));
    }
    setup();
}
