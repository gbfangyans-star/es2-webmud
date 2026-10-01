/* 無腸寶珠 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

// 種族裝備：只有無腸族能穿戴（使用者指定）。
varargs int wear(string on_part)
{
    object owner = environment();

    if( objectp(owner) && owner->query_race() != "woochan" )
        return notify_fail("只有無腸族才能穿戴這樣東西。\n");
    return ::wear(on_part);
}

void create()
{
    set_name("無腸寶珠", ({ "woochan ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 131000);
        set("long",
            "一枚做工精細的黃金戒指，但是輕得出奇，莫非是中空的？\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "spi": 2,
            "armor": 50,
            "int": 2,
            "wis": 2,
        ]));
    }
    setup();
}
