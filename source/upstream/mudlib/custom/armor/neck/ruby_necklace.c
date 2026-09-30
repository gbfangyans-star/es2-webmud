/* 紅寶石項鍊 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("\x1b[1;31m紅寶石項鍊\x1b[m", ({ "ruby necklace", "necklace" }));
    set_weight(200);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 10000);
        set("long",
            "一串金絲項鍊，墜子的地方是一顆耀眼的紅寶石。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "dodge": 5,
            "defense": 5,
        ]));
    }
    setup();
}
