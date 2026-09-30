/* 心殘爪 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("\x1b[1;33m心殘爪\x1b[m", ({ "heartless claw", "claw" }));
    set_weight(400);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 25000);
        set("long",
            "用狻猊的一雙前爪縫製而成的手套﹐看起來毛絨絨的﹐穿上去一定很暖和。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "damage": 15,
            "armor_vs_fire": -30,
        ]));
    }
    setup();
}
