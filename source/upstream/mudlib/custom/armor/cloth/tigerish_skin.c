/* 窮奇皮 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("窮奇皮", ({ "tigerish skin", "skin" }));
    set_weight(4000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 2000);
        set("long",
            "這是布滿了尖刺的窮奇的皮﹐只要披在身上就顯得十分凶猛。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "damage": 25,
            "intimidate": -30,
            "str": 2,
        ]));
    }
    setup();
}
