/* 黑龍戰袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;30m黑龍戰袍\x1b[m", ({ "black-dragon dress", "dress" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 30000);
        set("long",
            "一件黑龍戰袍。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "damage": 5,
            "attack": 10,
            "armor": 10,
        ]));
    }
    setup();
}
