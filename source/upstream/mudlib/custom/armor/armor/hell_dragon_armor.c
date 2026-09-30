/* 冥龍甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("冥龍甲", ({ "hell dragon armor", "armor" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 30000);
        set("long",
            "一件看起來十分沉重的盔甲。由于整件盔甲是用生鐵製成的﹐\n"
            "所以有著良好的防禦能力﹐不過多少會帶來一些行動上的不便。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "dodge": -5,
            "wittiness": 20,
            "armor": 30,
        ]));
    }
    setup();
}
