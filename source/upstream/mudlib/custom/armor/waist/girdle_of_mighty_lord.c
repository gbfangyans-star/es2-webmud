/* 霸王腰帶 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

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
    set_name("\x1b[1;37m霸王腰帶\x1b[m", ({ "girdle of mighty lord", "girdle" }));
    set_weight(300);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 25000);
        set("long",
            "一條用銀絲製成的腰帶，不僅擁有上層的防禦力，而且也很舒適。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "berserk": 10,
            "powerblow": 10,
        ]));
    }
    setup();
}
