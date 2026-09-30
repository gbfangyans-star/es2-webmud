/* 凝霜 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;37m凝霜\x1b[m", ({ "sword of holy frost", "sword" }));
    set_weight(16900);
    init_damage(3, 18, 80, 6, "twohanded sword");

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 65000);
        set("long",
            "凝霜劍﹐劍身長而寬﹐劍刃鋒利且散發出陣陣寒氣﹐正如寒冬的冰霜\n"
            "讓人不寒而顫。\n");
        set("apply_weapon/twohanded sword", ([
            "damage": 10,
            "force": 20,
            "armor_vs_ice": 80,
        ]));
    }
    setup();
}
