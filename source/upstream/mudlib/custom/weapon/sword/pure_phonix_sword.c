/* 妖蛇『鳳凰』劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;34m妖蛇\x1b[1;31m『鳳凰』\x1b[1;34m劍\x1b[m", ({ "pure-phonix sword", "sword" }));
    set_weight(7200);
    init_damage(3, 15, 100, 4, "sword");
    init_damage(3, 15, 100, 4, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 10000);
        set("long",
            "一把泛著淡紅色血光的短劍, 劍身是猶如一條『金蛇』﹐華麗無比﹐\n"
            "劍柄為一『鳳凰』身﹐燃燒的火鳳凰是紅光的來源。\n");
        set("apply_weapon/sword", ([
            "attack": 30,
        ]));
        set("apply_weapon/secondhand sword", ([
            "attack": 30,
        ]));
    }
    setup();
}
