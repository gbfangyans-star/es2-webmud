/* 混天白龍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;37m混天白龍\x1b[m", ({ "white-dragon plate", "plate" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 100000);
        set("long",
            "一件雪白色的鎧甲, 鎧甲的前胸浮刻著一條栩栩如生的白色\n"
            "錦龍。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 25,
            "armor_vs_ice": 50,
            "throwing": 10,
        ]));
    }
    setup();
}
