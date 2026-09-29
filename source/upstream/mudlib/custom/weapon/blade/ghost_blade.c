/* 幽冥魔刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;33m幽冥魔刀\x1b[m", ({ "ghost blade", "blade" }));
    set_weight(30000);
    init_damage(4, 30, 195, 4, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 65000);
        set("long",
            "一柄細長似劍似刀的薄刀, 刀柄是一根巨獸的骸骨, 刀身朦朧似乎可以透\n"
            "視過去, 且散發出至陰至邪的寒意。此刀相傳乃刀魔齊燁所執, 五百年前\n"
            "於大漠與刀鬼戈魯戊齊決戰中遺失, 至今一直無人見過此刀。\n");
        set("apply_weapon/twohanded blade", ([
            "intimidate": 50,
            "wittiness": 50,
            "armor_vs_lightning": 100,
        ]));
    }
    setup();
}
