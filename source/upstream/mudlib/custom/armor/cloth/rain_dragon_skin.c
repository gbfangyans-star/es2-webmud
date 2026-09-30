/* 天龍鱗 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;36m天龍鱗\x1b[m", ({ "rain dragon skin", "skin" }));
    set_weight(4000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 65000);
        set("long",
            "這是天龍鱗片的一部份，裹在身上可以當作衣服，有相當不錯的防禦力。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "wis": 2,
            "attack": -10,
            "armor": 20,
            "armor_vs_ice": 100,
        ]));
    }
    setup();
}
