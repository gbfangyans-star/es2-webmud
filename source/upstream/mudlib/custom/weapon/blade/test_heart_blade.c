/* 磨心刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("磨心刀", ({ "test-heart blade", "blade" }));
    set_weight(8300);
    init_damage(4, 14, 110, 1, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 65400);
        set("long",
            "一把看起來極為普通的長刀﹐刀身已經有些破損了﹐但是看的出\n"
            "刀的主人還是異常珍愛這把刀。此刀雖然不很出眾﹐但卻有刀控\n"
            "人性的魔力﹐據說歷來此刀的主人都漸漸變得十分殘忍。\n");
        set("apply_weapon/blade", ([
            "damage": 10,
            "cor": 3,
        ]));
    }
    setup();
}
