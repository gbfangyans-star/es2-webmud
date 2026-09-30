/* 白熊護甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;37m白熊護甲\x1b[m", ({ "bear armor", "armor" }));
    set_weight(5000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 35000);
        set("long",
            "一套由千年白熊的皮所製作而成的護甲，聽說穿了此護甲能不怕寒冷。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "dodge": -5,
            "armor_vs_ice": 20,
            "armor": 30,
        ]));
    }
    setup();
}
