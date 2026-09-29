/* 煉獄 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;31m煉獄\x1b[0m", ({ "blade of inferno", "blade" }));
    set_weight(19400);
    init_damage(4, 17, 172, 4, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 85000);
        set("long",
            "一把背串銅環的七尺大刀，在日光之下映射出一輪暗紅色的光環，猶如\n"
            "一股來自地獄的火焰，吞噬著人間的一切生命。\n");
        set("apply_weapon/twohanded blade", ([
            "damage": 10,
            "intimidate": 15,
        ]));
    }
    setup();
}
