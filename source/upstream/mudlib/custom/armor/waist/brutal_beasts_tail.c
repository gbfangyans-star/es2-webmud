/* 雍和尾 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("\x1b[1;31m雍和尾\x1b[m", ({ "brutal beast's tail", "tail" }));
    set_weight(1000);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 100000);
        set("long",
            "這是豐山怪獸雍和的尾巴，看起來毛絨絨的，圍在腰間應該不錯。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "spell": 5,
            "damage": 5,
            "armor": 15,
            "armor_vs_ice": 50,
        ]));
    }
    setup();
}
