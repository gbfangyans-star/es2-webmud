/* 冥魂戰鎧 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;37m冥魂戰鎧\x1b[m", ({ "ghost-hell plate", "plate" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 30000);
        set("long",
            "一件散發著陰氣的戰甲﹐上面細細的雕滿了一百又八個不同樣式的冤魂\n"
            "野鬼。據說﹐這種雕花是一種來自陰間的詛咒﹐在提昇某種能力的同時\n"
            "會大幅度的降低其他的能力﹐所以﹐天朝的工匠們稱這類裝備為詛咒系\n"
            "裝備。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 20,
            "damage": 10,
            "cor": 1,
        ]));
    }
    setup();
}
