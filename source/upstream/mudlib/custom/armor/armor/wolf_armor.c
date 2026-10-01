/* 狼皮護甲 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("狼皮護甲", ({ "wolf armor", "armor" }));
    set_weight(5000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 43000);
        set("long",
            "由皮帶所綁起的兩張狼皮，分別罩住左半身和右半身，有保暖的效\n"
            "用，在防護力上則十分有限。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 5,
            "move": 25,
            "attack": 5,
        ]));
    }
    setup();
}
