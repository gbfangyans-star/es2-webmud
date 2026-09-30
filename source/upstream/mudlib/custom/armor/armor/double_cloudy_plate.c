/* 兩儀雲龍甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;37m兩儀雲龍甲\x1b[m", ({ "double cloudy plate", "plate" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 20000);
        set("long",
            "這是一件用白銀打造的鎧甲，鎧甲的正面鑲有一條白金的雲龍，雲\n"
            "龍的四周還精心的雕有許多白雲。這件鎧甲的價值想來不低，但是\n"
            "防禦能力似乎不是很好。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 15,
            "armor_vs_wind": 75,
            "intimidate": 50,
        ]));
    }
    setup();
}
