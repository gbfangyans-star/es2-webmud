/* 龍紋斬馬刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;33m龍紋\x1b[m斬馬刀", ({ "reckless blade", "blade" }));
    set_weight(19400);
    init_damage(4, 17, 172, 4, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 25000);
        set("long",
            "一把背串銅環的七尺斬馬大刀，與眾不同的是，此刀的刀背上鑲有一條銅\n"
            "製的臥龍，不僅美觀了許多，額外的重量也提高了此刀的殺傷力。\n");
        set("apply_weapon/twohanded blade", ([
            "damage": 10,
            "attack": 10,
            "tiger-blade": 15,
        ]));
    }
    setup();
}
