/* 紫羅點翠戰甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;35m紫羅點翠戰甲\x1b[m", ({ "armor of violet rohan", "armor" }));
    set_weight(8000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 5000);
        set("long",
            "紫羅點翠甲相傳是在一千年前鄔赤族中一個神秘而富有智慧的法師, 為了打造一套刀\n"
            "槍不入的盔甲, 而將部份法力傳入一位當時富有盛名之鐵匠所打造的戰甲之中, 而成\n"
            "了難得一見的戰甲, 由於戰甲中鑲有綠翠, 故稱『紫羅點翠甲』。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "con": 1,
            "defense": 20,
            "armor": 25,
        ]));
    }
    setup();
}
