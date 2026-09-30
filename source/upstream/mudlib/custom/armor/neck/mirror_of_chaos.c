/* 混沌之鏡 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("\x1b[1;37m混沌之鏡\x1b[m", ({ "mirror of chaos", "mirror" }));
    set_weight(500);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "面");
        set("value", 5000);
        set("long",
            "一面散發著幽暗之光的古鏡，仔細看似乎有甚麼東西試圖躍出鏡面。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "damage": 10,
            "intimidate": 25,
            "cor": 1,
        ]));
    }
    setup();
}
