/* 雷火天狼罩 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("雷火天狼罩", ({ "fire-wolf cloak", "cloak" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 10000);
        set("long",
            "一件紫紅色的蓋頭罩袍, 袍後繡著一個面目猙獳的狼頭。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "spells": 5,
            "taoism-fire": 5,
            "armor": 5,
        ]));
    }
    setup();
}
