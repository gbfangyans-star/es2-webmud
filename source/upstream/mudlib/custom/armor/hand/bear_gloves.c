/* 白熊套手 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("\x1b[1;37m白熊套手\x1b[m", ({ "bear gloves", "gloves" }));
    set_weight(400);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 20000);
        set("long",
            "一雙由千年白熊的手掌所製做而成的套手，其套手外觀都是一片雪白的毛。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "parry": 10,
        ]));
    }
    setup();
}
