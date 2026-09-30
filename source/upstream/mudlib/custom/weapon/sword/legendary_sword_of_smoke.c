/* 殘煙劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("殘煙劍", ({ "legendary sword of smoke", "sword" }));
    set_weight(6200);
    init_damage(2, 20, 100, 2, "sword");
    init_damage(2, 10, 100, 2, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 25000);
        set("long",
            "一把纖細的短劍﹐劍身若有若無﹐日光下猶如荒涼大漠中的一縷孤煙......\n");
        set("apply_weapon/sword", ([
            "virtual sword": 10,
            "force": -5,
            "parry": 10,
        ]));
        set("apply_weapon/secondhand sword", ([
            "intimidate": 10,
            "secondhand sword": 20,
            "force": -5,
            "cps": 2,
        ]));
    }
    setup();
}
