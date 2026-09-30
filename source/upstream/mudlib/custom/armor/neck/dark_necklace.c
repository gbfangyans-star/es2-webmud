/* 闇之項鏈 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

// 原資料「職業限制：盜賊」：只有盜賊能穿戴。
varargs int wear(string on_part)
{
    object owner = environment();

    if( objectp(owner) && owner->query_class() != "thief" )
        return notify_fail("只有盜賊才能穿戴這樣東西。\n");
    return ::wear(on_part);
}

void create()
{
    set_name("\x1b[1;30m闇之項鏈\x1b[m", ({ "dark necklace", "necklace" }));
    set_weight(200);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 3000);
        set("long",
            "一串用黑色細絲線串起來的黑色小木珠。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "backstab": 5,
            "damage": 5,
            "awarness": 50,
        ]));
    }
    setup();
}
