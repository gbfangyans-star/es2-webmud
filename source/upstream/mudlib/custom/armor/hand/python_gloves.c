/* 玉蟒鱗護 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("\x1b[1;32m玉蟒鱗護\x1b[m", ({ "python gloves", "gloves" }));
    set_weight(400);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 10000);
        set("long",
            "取青蟒鱗皮製成，雪蠶絲為輔，以手工反覆交織而成，韌性極佳，觸\n"
            "之冷若冰雪，卻又如羽般輕柔。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "attack": 15,
            "cor": 1,
        ]));
    }
    setup();
}
