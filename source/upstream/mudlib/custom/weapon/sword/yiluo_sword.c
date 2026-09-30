/* 易羅大劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("易羅大劍", ({ "yiluo sword", "sword" }));
    set_weight(16100);
    init_damage(3, 18, 120, 2, "twohanded sword");

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 9000);
        set("long",
            "為蔭百邪鬼將的兵器, 劍尖隱隱散著陣陣幽光。\n");
        set("apply_weapon/twohanded sword", ([
            "defense": 30,
            "armor_vs_wind": 50,
        ]));
    }
    setup();
}
