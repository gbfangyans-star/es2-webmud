/* 遮陽大帽 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("遮陽大帽", ({ "sun helmet", "helmet" }));
    set_weight(300);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 500);
        set("long",
            "一頂大帽, 頗具遮陽防曬之效.\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor_vs_fire": 5,
        ]));
    }
    setup();
}
