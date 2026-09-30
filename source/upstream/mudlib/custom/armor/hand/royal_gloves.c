/* 霸王手套 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

// 原資料「職業限制：軍人」：只有軍人能穿戴。
varargs int wear(string on_part)
{
    object owner = environment();

    if( objectp(owner) && owner->query_class() != "soldier" )
        return notify_fail("只有軍人才能穿戴這樣東西。\n");
    return ::wear(on_part);
}

void create()
{
    set_name("\x1b[1;37m霸王手套\x1b[m", ({ "royal gloves", "gloves" }));
    set_weight(400);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 10000);
        set("long",
            "亮白色的手套，指尖的地方是露出來的，手背上有三片銀亮的金\n"
            "屬，可以讓軍人在戰場上得以盡情發揮。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "berserk": 5,
            "powerblow": 5,
        ]));
    }
    setup();
}
