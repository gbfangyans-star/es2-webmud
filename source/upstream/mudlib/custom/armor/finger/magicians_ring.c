/* 七幻寶戒 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

// 原資料「職業限制：道士」：只有道士能穿戴。
varargs int wear(string on_part)
{
    object owner = environment();

    if( objectp(owner) && owner->query_class() != "taoist" )
        return notify_fail("只有道士才能穿戴這樣東西。\n");
    return ::wear(on_part);
}

void create()
{
    set_name("七幻寶戒", ({ "magician's ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 100000);
        set("long",
            "一枚十分可愛的戒指﹐上面精細的雕刻著多種奇妙的花紋。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "wis": 2,
            "magic": 10,
            "armor": 10,
        ]));
    }
    setup();
}
