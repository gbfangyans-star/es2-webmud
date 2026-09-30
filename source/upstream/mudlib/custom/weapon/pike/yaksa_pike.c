/* 夜叉戢 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("夜叉戢", ({ "yaksa pike", "pike" }));
    set_weight(15700);
    init_damage(5, 10, 100, 4, "twohanded pike");

    if( !clonep() ) {
        set("wield_as", "twohanded pike");
        set("unit", "把");
        set("value", 15000);
        set("long",
            "籠罩在夜叉戢上的紫色霧氣是由百種妖氣結合而成, 此槍在槍頭處刻有鳳凰標誌。\n");
        set("apply_weapon/twohanded pike", ([
            "attack": 15,
            "parry": 10,
            "heavy_parry": 10,
        ]));
    }
    setup();
}
