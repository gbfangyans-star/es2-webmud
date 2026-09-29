/* 軒轅龍骨刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[0;33m軒轅\x1b[1;37m龍骨\x1b[0;33m刀\x1b[m", ({ "blade of dragon", "blade" }));
    set_weight(19400);
    init_damage(4, 17, 172, 4, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 70000);
        set("long",
            "軒轅龍骨刀刀身長而寬刀刃寒光四射。此刀雖為千古名刀，但是卻因其刀\n"
            "身奇重，所以很少有人可以將其威力儘數發揮。\n");
        set("apply_weapon/twohanded blade", ([
            "attack": 30,
        ]));
    }
    setup();
}
