/* 銀絲戰袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;37m銀絲戰袍\x1b[m", ({ "silver cloth", "cloth" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 2000);
        set("long",
            "這是一件用銀白色的絲綢縫製而成的長袍，不僅美觀大方，而且據有\n"
            "不俗的防禦力。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 10,
            "attack": 30,
            "armor_vs_ice": 100,
        ]));
    }
    setup();
}
