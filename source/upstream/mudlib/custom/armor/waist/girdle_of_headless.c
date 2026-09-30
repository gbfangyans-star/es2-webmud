/* 形天之怒 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

// 原資料「種族限制：形天」：只有形天族能穿戴。
varargs int wear(string on_part)
{
    object owner = environment();

    if( objectp(owner) && owner->query_race() != "headless" )
        return notify_fail("只有形天族才能穿戴這樣東西。\n");
    return ::wear(on_part);
}

void create()
{
    set_name("形天之怒", ({ "girdle of headless", "girdle" }));
    set_weight(800);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 70000);
        set("long",
            "這條腰帶無論是款式還是做工都可以明顯的看出是專為形天族人打造的。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "cor": 2,
            "intimidate": 10,
            "defense": 10,
        ]));
    }
    setup();
}
