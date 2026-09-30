/* 西巫袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("西巫袍", ({ "malik robe", "robe" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 5000);
        set("long",
            "一件由不知名的布料織成的藏青色道袍，傳聞中此袍特意為巫首\n"
            "族人設計，下擺特長蓋過於腳，以致於其他種族穿戴起來走路極\n"
            "為不便。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "spells": 10,
            "spell": 25,
        ]));
    }
    setup();
}
