/* 浴血戰袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[0;31m浴血戰袍\x1b[m", ({ "blood cloth", "cloth" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 15000);
        set("long",
            "這是一件看起來就非常耀眼的長袍, 據說是天寒村中遺失的寶衣, 據\n"
            "說是每個練武的人都非常想得到的一件寶物。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "intimidate": 50,
            "armor": 5,
        ]));
    }
    setup();
}
