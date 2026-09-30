/* 天都劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;36m天都劍\x1b[m", ({ "heaven sword", "sword" }));
    set_weight(7200);
    init_damage(3, 15, 100, 4, "sword");
    init_damage(3, 7, 100, 4, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 40000);
        set("long",
            "天都劍比一般短劍長出吋許，而比水月短了些，劍刃薄如蝶翼，\n"
            "劍身透著天藍色的光輝，雖然較水月沉重了點，但握在手中仍猶\n"
            "如無物，的確是把罕見的寶劍。天都與水月是兩把特地打造的對\n"
            "劍，從重量到長度都配合的近乎完美，當雙劍齊出之時，甚至會\n"
            "有超乎想像的攻擊力。\n");
        set("apply_weapon/secondhand sword", ([
            "secondhand sword": 10,
            "attack": 25,
        ]));
    }
    setup();
}
