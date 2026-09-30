/* 水月劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;34m水月劍\x1b[m", ({ "night sword", "sword" }));
    set_weight(7200);
    init_damage(3, 15, 100, 4, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 10000);
        set("long",
            "水月劍比天都劍長了一些，卻仍然不能與一般長劍相比，劍刃薄\n"
            "如蝶翼，劍身透著海藍色的光輝，劍刃雖較天都長，卻是猶如鴻\n"
            "毛般的輕巧，揮舞起來完全不受窒礙，是把難得一見的寶劍。天\n"
            "都與水月是兩把特地打造的對劍，從重量到長度都配合的近乎完\n"
            "美，當雙劍齊出之時，甚至會有超乎想像的攻擊力。\n");
        set("apply_weapon/sword", ([
            "sword": 10,
            "defense": 25,
        ]));
    }
    setup();
}
