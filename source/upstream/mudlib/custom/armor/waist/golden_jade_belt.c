/* 金絲翡翠帶 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("金絲翡翠帶", ({ "golden jade belt", "belt" }));
    set_weight(800);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 71000);
        set("long",
            "一條用金絲縫製，內嵌數塊上好翡翠的腰帶。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "intimidate": 25,
            "move": 50,
            "armor": 30,
            "armor_vs_ice": 100,
        ]));
    }
    setup();
}
