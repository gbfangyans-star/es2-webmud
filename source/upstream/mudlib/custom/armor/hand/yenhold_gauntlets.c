/* 厭火之拳 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

// 種族裝備：只有厭火族能穿戴（使用者指定）。
varargs int wear(string on_part)
{
    object owner = environment();

    if( objectp(owner) && owner->query_race() != "yenhold" )
        return notify_fail("只有厭火族才能穿戴這樣東西。\n");
    return ::wear(on_part);
}

void create()
{
    set_name("厭火之拳", ({ "yenhold gauntlets", "gauntlets" }));
    set_weight(400);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 22000);
        set("long",
            "一副十分結實的厚厚的手套，看起來很保暖，也許會太暖了 ...\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor_vs_fire": 100,
            "armor": 50,
            "defense": 50,
        ]));
    }
    setup();
}
