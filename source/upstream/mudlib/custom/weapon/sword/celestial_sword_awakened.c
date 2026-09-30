/* 『穿靈』 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;31m『\x1b[1;37m穿靈\x1b[1;31m』\x1b[m", ({ "celestial sword", "sword" }));
    set_weight(9400);
    init_damage(3, 20, 150, 5, "sword");
    init_damage(3, 20, 150, 5, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 10000);
        set("long",
            "以參龍『麒麟』﹐妖蛇『鳳凰』﹐朱雀『白虎』和玄武『青龍』四大妖劍\n"
            "為身的聖劍。劍柄處一枚火紅的寶石呼喚著穿靈沉睡的力量。寒於氏就是\n"
            "以此劍斬下妖魔「侮天鬼」的頭顱\n");
        set("apply_weapon/sword", ([
            "damage": 20,
            "intimidate": 35,
            "armor": 25,
        ]));
        set("apply_weapon/secondhand sword", ([
            "damage": 20,
            "intimidate": 35,
            "armor": 25,
        ]));
    }
    setup();
}
