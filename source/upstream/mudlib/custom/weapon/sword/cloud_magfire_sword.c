/* 紫炎劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("紫炎劍", ({ "cloud magfire sword", "sword" }));
    set_weight(6100);
    init_damage(2, 20, 80, 1, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 95000);
        set("long",
            "一把由玄鐵石打造出來的劍,劍身還不時的散發出\n"
            "微微的紫色火燄,相傳是紫雲宮的鎮門寶劍的其中\n"
            "一把 !\n");
        set("apply_weapon/sword", ([
            "dex": 1,
            "str": 1,
            "wis": -1,
            "sword": 5,
        ]));
    }
    setup();
}
