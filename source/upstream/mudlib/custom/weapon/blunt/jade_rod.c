/* 寒玉藥杵 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("\x1b[1;37m寒玉藥杵\x1b[0m", ({ "jade rod", "blunt" }));
    set_weight(6600);
    init_damage(3, 15, 115, 0, "blunt");

    if( !clonep() ) {
        set("wield_as", "blunt");
        set("unit", "把");
        set("value", 100000);
        set("long",
            "這是一把用上古寒玉雕琢成的藥杆，浸染日久竟也隱隱收著藥石之氣。\n");
        set("apply_weapon/blunt", ([
            "alchemy-medication": 20,
            "armor_vs_ice": 50,
            "wis": 1,
        ]));
    }
    setup();
}
