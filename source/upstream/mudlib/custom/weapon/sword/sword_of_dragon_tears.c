/* 泣龍怨 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;36m泣龍怨\x1b[m", ({ "sword of dragon tears", "sword" }));
    set_weight(16900);
    init_damage(3, 18, 80, 6, "twohanded sword");

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 95000);
        set("long",
            "此劍劍身薄到近可透光, 無鞘之設計則是讓使劍者能在第一時刻快速斬\n"
            "殺對手, 同時劍身倍於一般常見,且劍身極為柔軟, 一望便知是名劍.\n");
        set("apply_weapon/twohanded sword", ([
            "attack": 25,
            "twohanded sword": 10,
        ]));
    }
    setup();
}
