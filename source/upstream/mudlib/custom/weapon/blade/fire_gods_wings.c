/* 火神之翼 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;31m火神之翼\x1b[m", ({ "fire god's wings", "blade" }));
    set_weight(21800);
    init_damage(4, 20, 195, 4, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 50000);
        set("long",
            "這是一把火光閃耀的百斤大刀。刀身造型典雅，猶如展開的鳳凰的翅膀。鋒利\n"
            "的刀刃上紅光閃現，仿彿燃燒著來自地獄的火焰，使人產生一種難以抵抗的壓\n"
            "迫感。\n");
        set("apply_weapon/twohanded blade", ([
            "cor": 4,
            "armor_vs_fire": 150,
            "damage": 30,
            "taoism-fire": 30,
        ]));
    }
    setup();
}
