/* 灰袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("灰袍", ({ "gray robe", "robe" }));
    set_weight(6000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 25000);
        set("long",
            "一件灰布長袍，看起來不怎麼起眼，但仔細一看內裡竟縫著一層金屬絲網。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor_vs_fire": 10,
            "armor_vs_ice": 10,
            "defense": 5,
            "armor": 10,
        ]));
    }
    setup();
}
