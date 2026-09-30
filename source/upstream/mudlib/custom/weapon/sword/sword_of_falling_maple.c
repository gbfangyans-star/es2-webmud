/* 落楓劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("落楓劍", ({ "sword of falling maple", "sword" }));
    set_weight(7200);
    init_damage(3, 15, 100, 4, "sword");
    init_damage(3, 7, 100, 4, "secondhand sword");

    if( !clonep() ) {
        set("wield_as", ({ "sword", "secondhand sword" }));
        set("unit", "把");
        set("value", 80000);
        set("long",
            "一把造型優雅的古劍﹐稍顯蒼老的劍刃依然散發著寒冷的劍氣。\n");
        set("apply_weapon/sword", ([
            "lunmay": 10,
            "dodge": 10,
        ]));
        set("apply_weapon/secondhand sword", ([
            "parry": -5,
            "dodge": 10,
            "advance_lunmay": 10,
        ]));
    }
    setup();
}
