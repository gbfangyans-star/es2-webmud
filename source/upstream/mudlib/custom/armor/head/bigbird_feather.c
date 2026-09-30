/* 飛涎羽 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("\x1b[1;36m飛涎羽\x1b[0m", ({ "bigbird feather", "feather" }));
    set_weight(100);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "根");
        set("value", 40000);
        set("long",
            "巨鳥飛涎的羽毛，有輕身、防火、避雷的神奇功效。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor_vs_fire": 40,
            "dodge": 5,
            "armor_vs_lightning": 80,
        ]));
    }
    setup();
}
