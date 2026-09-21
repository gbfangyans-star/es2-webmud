#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("冶磺套", ({ "fire gauntlets", "gauntlets" }));
    set_weight(3000);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 4000);
        set("long",
            "一副外觀十分精巧之手套, 數片黃色金屬覆蓋其上, 內襯為某種皮毛, 據聞為某得道\n"
            "高人苦思練丹之法時, 所特別裁出之防具, 可防高熱。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor_vs_fire": 50,
            "armor": 30,
            "damage_vs_fire": 20,
        ]));
    }

    setup();
}
