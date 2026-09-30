/* 無形心鏡 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;34m無形心鏡\x1b[m", ({ "shapeless heartguard", "heartguard" }));
    set_weight(2000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "面");
        set("value", 25000);
        set("long",
            "一面閃著深藍色光芒的護心鏡，觸手冰涼，份量也不輕。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "con": 1,
            "armor_vs_wind": 50,
            "armor": 5,
            "armor_vs_lightning": 50,
        ]));
    }
    setup();
}
