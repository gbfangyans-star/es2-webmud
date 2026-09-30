/* 十石大斧 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("十石大斧", ({ "grandaxe", "axe" }));
    set_weight(32000);
    init_damage(3, 30, 165, 9, "twohanded axe");

    if( !clonep() ) {
        set("wield_as", "twohanded axe");
        set("unit", "把");
        set("value", 20000);
        set("long",
            "這是一種非常瀋重的戰斧﹐斧刃中間還裝有尖刺。\n");
        set("apply_weapon/twohanded axe", ([
            "damage": 10,
            "armor_vs_fire": 50,
            "twohanded axe": 10,
        ]));
    }
    setup();
}
