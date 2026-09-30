/* 八鬼牙斧 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("\x1b[1;33m八鬼牙斧\x1b[m", ({ "eight-ghost axe", "axe" }));
    set_weight(24900);
    init_damage(3, 30, 146, 9, "twohanded axe");

    if( !clonep() ) {
        set("wield_as", "twohanded axe");
        set("unit", "把");
        set("value", 90000);
        set("long",
            "一把用千歲惡鬼的巨大牙齒製成的斧頭。此斧斧刃上有一層血跡，不知\n"
            "有多少人被此斧斬殺，斧背上所刻的詛咒符文據說可以封住被殺者的靈\n"
            "魂，使其永世不得超生。\n");
        set("apply_weapon/twohanded axe", ([
            "attack": 30,
            "twohanded axe": 15,
        ]));
    }
    setup();
}
