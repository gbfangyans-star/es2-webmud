/* 藍涎刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;36m藍涎刀\x1b[0m", ({ "blue_poison blade", "blade" }));
    set_weight(6100);
    init_damage(3, 12, 90, 5, "blade");
    init_damage(3, 6, 90, 5, "secondhand blade");

    if( !clonep() ) {
        set("wield_as", ({ "blade", "secondhand blade" }));
        set("unit", "把");
        set("value", 75000);
        set("long",
            "這是一把細長的單刀, 在刀鋒的部份有著一絲絲淺藍色的水紋...。\n");
        set("apply_weapon/secondhand blade", ([
            "blade": 10,
            "attack": 20,
        ]));
    }
    setup();
}

// 單手或左手使用時，每次命中都會上毒（見 daemon/condition/blue_venom.c）。
void hit_ob(object me, object victim, int damage)
{
    if( victim->query("life_form") == "ghost" ) return;
    "/daemon/condition/blue_venom"->poison(victim, me);
}
