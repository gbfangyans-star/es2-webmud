/* 聖龍甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("聖龍甲", ({ "dragon armor", "armor" }));
    set_weight(8000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 120000);
        set("long",
            "一件金鏤內襯，外披精鋼鐵環的鍊子甲，乃是專為沙場戰將所打造\n"
            "的上品戰甲，有著強大的防護力。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "str": 2,
            "cor": 2,
            "defense": 10,
            "armor": 40,
        ]));
    }
    setup();
}
