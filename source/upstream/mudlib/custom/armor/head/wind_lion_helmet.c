/* 風獅吞面盔 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("風獅吞面盔", ({ "wind lion helmet", "helmet" }));
    set_weight(800);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 30000);
        set("long",
            "這是一頂用奇獸風獅的頭骨打造的頭盔，依然保留了風獅的部份神力。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor_vs_wind": 10,
            "dodge": 10,
            "taoism-storm": 10,
        ]));
    }
    setup();
}
