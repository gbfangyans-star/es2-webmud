/* 光鎧 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;37m光鎧\x1b[m", ({ "light plate", "plate" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 3300);
        set("long",
            "一件有著柔柔白光的鎧甲。材質不明，是凌承軒的一位故人所贈的\n"
            "異世寶物。因為輕巧，凌月蘅都隨身穿著它。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor_vs_wind": 25,
            "armor_vs_lightning": 100,
            "armor": 5,
            "dodge": 10,
        ]));
    }
    setup();
}
