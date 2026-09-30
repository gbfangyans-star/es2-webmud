/* 鬼纓槍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("\x1b[1;31m鬼纓槍\x1b[m", ({ "ghost pike", "pike" }));
    set_weight(23000);
    init_damage(4, 20, 150, 10, "twohanded pike");

    if( !clonep() ) {
        set("wield_as", "twohanded pike");
        set("unit", "把");
        set("value", 30000);
        set("long",
            "一桿槍尖閃著慘綠色光芒的長槍，槍桿渾體透紅，觸手冰涼，不像是會出現在人世間的兵器。\n");
        set("apply_weapon/twohanded pike", ([
            "attack": 20,
            "defense": 30,
        ]));
    }
    setup();
}
