/* 雷光戢 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("\x1b[1;33m雷光戢\x1b[m", ({ "lightning pike", "pike" }));
    set_weight(15700);
    init_damage(5, 10, 100, 4, "twohanded pike");

    if( !clonep() ) {
        set("wield_as", "twohanded pike");
        set("unit", "把");
        set("value", 35000);
        set("long",
            "此戢戢頭分三叉，三叉之上各刻有無數咒文。三道金色雷光纏繞在\n"
            "三叉之上，發出耀眼的光芒。\n");
        set("apply_weapon/twohanded pike", ([
            "armor_vs_lightning": 50,
            "taoism-thunder": 10,
            "wis": 2,
        ]));
    }
    setup();
}
