/* 狙首盔 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("狙首盔", ({ "monkey helmet", "helmet" }));
    set_weight(800);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 5000);
        set("long",
            "這是用上古妖獸「狙」的頭骨做成的頭盔﹐不過戴起來的話似乎\n"
            "不會很好看。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "mysticism": 5,
            "dodge": 5,
        ]));
    }
    setup();
}
