/* 巴蛇大矛 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("巴蛇大矛", ({ "hydra lance", "pike" }));
    set_weight(17100);
    init_damage(4, 14, 90, 5, "twohanded pike");

    if( !clonep() ) {
        set("wield_as", "twohanded pike");
        set("unit", "把");
        set("value", 50000);
        set("long",
            "一柄用生鐵打造的長矛，雖然稍顯沉重﹐但是其強大的殺傷力仍使其成為\n"
            "眾多天朝武將喜愛的武器。\n");
        set("apply_weapon/twohanded pike", ([
            "damage": 20,
            "parry": 10,
        ]));
    }
    setup();
}
