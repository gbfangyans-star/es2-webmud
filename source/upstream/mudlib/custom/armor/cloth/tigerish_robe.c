/* 虎皮長袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[0;33m虎皮長袍\x1b[m", ({ "tigerish robe", "robe" }));
    set_weight(4000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 3500);
        set("long",
            "一件用虎皮縫製的長袍，毛絨絨的，穿上一定很暖和。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "wittiness": -50,
            "damage": 10,
            "intimidate": 25,
        ]));
    }
    setup();
}
