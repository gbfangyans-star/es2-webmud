/* 天王鞭 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_WHIP;

void create()
{
    set_name("天王鞭", ({ "god whip", "whip" }));
    set_weight(7300);
    init_damage(3, 14, 85, 8, "whip");

    if( !clonep() ) {
        set("wield_as", "whip");
        set("unit", "把");
        set("value", 90000);
        set("long",
            "用玄鐵打造的十三節鞭，雖然很重而且用起來不夠靈活，但是其\n"
            "強大的殺傷力卻是不容忽視的。\n");
        set("apply_weapon/whip", ([
            "attack": 10,
            "dex": -1,
            "dodge": -5,
            "str": 1,
        ]));
    }
    setup();
}
