/* 靈中樞甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

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
    set_name("\x1b[1;34m靈中樞甲\x1b[m", ({ "soul lapis lazuli plate", "plate" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 140000);
        set("long",
            "一件湛藍色的寶甲，由無數片青金石以烏金絲線縫合，由內以外共縫合\n"
            "了五層。仔細的看，可看到每一片青金石上都面雕刻了一個骷髏頭。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 40,
            "wittiness": 20,
            "wis": 3,
        ]));
    }
    setup();
}
