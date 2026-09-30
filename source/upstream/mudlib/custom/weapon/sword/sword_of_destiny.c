/* 命運之刃 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;37m命運之刃\x1b[m", ({ "sword of destiny", "sword" }));
    set_weight(19000);
    init_damage(3, 22, 140, 4, "twohanded sword");

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 45000);
        set("long",
            "這是一把雪白的重劍，劍身寬扁微微鼓起，劍刃寒光閃耀，讓人不敢\n"
            "直視。據說，此劍頗具靈性，當主人死亡時會隨主人一同毀滅。\n");
        set("apply_weapon/twohanded sword", ([
            "cor": 3,
            "defense": 20,
            "attack": 20,
        ]));
    }
    setup();
}
