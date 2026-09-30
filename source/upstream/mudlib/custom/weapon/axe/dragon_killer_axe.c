/* 斬龍斧 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("\x1b[1;37m斬龍斧\x1b[m", ({ "dragon-killer axe", "axe" }));
    set_weight(24900);
    init_damage(3, 30, 146, 9, "twohanded axe");

    if( !clonep() ) {
        set("wield_as", "twohanded axe");
        set("unit", "把");
        set("value", 55000);
        set("long",
            "一把看起來很普通的巨斧﹐整把斧頭給人一種古樸的感覺。\n"
            "斧刃處已經稍有破損﹐不過還是打磨得十分鋒利﹐日光下不\n"
            "停的散發出陣陣寒光。\n");
        set("apply_weapon/twohanded axe", ([
            "damage": 15,
            "attack": 30,
        ]));
    }
    setup();
}
