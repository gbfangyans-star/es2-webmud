/* 雍和爪 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("\x1b[1;31m雍和爪\x1b[m", ({ "brutal beast's claw", "claw" }));
    set_weight(800);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 25000);
        set("long",
            "這是豐山怪獸雍和的雙爪，似乎可以套在手上。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "spell": 10,
            "damage": 10,
            "armor": 5,
        ]));
    }
    setup();
}
