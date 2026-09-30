/* 巨劍『破石』 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;37m巨劍『破石』\x1b[m", ({ "smashing sword", "sword" }));
    set_weight(22000);
    init_damage(4, 20, 97, 5, "twohanded sword");

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 35000);
        set("long",
            "一把沉重的精鋼巨劍, 非具神力之人便無法揮動如此沉重的神兵利器,\n"
            "其破石如斬木之輕易, 故曰\x1b[1;37m巨劍『破石』\x1b[m。\n");
        set("apply_weapon/twohanded sword", ([
            "attack": 20,
            "damage": 10,
        ]));
    }
    setup();
}
