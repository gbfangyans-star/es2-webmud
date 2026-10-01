/* 厭火之拳 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

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
