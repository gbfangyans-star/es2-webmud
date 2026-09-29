/* 軒轅龍骨刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;33m軒轅\x1b[1;37m龍骨\x1b[1;33m刀\x1b[m", ({ "blade of dragon", "blade" }));
    set_weight(19400);
    init_damage(4, 17, 172, 4, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 40000);
        set("long",
            "\x1b[1;33m軒轅\x1b[1;37m龍骨\x1b[1;33m刀\x1b[m刀身長而寬刀刃寒光四射，豪光萬丈。此刀雖為千古名刀，但\n"
            "卻因其刀身奇重，所以很少有人可以將其深藏其中的天龍之力儘數發揮。\n");
        set("apply_weapon/twohanded blade", ([
            "attack": 50,
            "wittiness": 50,
        ]));
    }
    setup();
}
