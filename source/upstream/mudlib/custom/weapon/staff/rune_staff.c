/* 禁符之杖 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("禁符之杖", ({ "rune staff", "staff" }));
    set_weight(10200);
    init_damage(2, 12, 60, 3, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 21000);
        set("long",
            "這是一種幫助法師施法的法器﹐杖端是一個圓形的鎖片﹐刻著禁符咒\n"
            "──一種避免法力散失的符咒。\n");
        set("apply_weapon/twohanded staff", ([
            "magic": 10,
            "mao-shan mysticism": 10,
        ]));
    }
    setup();
}
