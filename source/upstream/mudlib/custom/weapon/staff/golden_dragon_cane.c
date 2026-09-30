/* 金龍杖 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("金龍杖", ({ "golden dragon cane", "staff" }));
    set_weight(17300);
    init_damage(4, 13, 150, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 15000);
        set("long",
            "一根中等長度的黃銅杖﹐杖上嵌有一條用黃金製造的龍。\n");
        set("apply_weapon/twohanded staff", ([
            "force": 5,
            "parry": 10,
            "attack": 10,
        ]));
    }
    setup();
}
