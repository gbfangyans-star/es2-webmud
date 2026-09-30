/* 七彩琉璃匕 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("七彩琉璃匕", ({ "beauty dagger", "dagger" }));
    set_weight(6300);
    init_damage(3, 12, 75, 7, "dagger");
    init_damage(3, 12, 75, 7, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 5000);
        set("long",
            "一把光鮮亮麗的匕首, 匕首上鑲著的寶石隱隱泛出七彩寶光.\n");
        set("apply_weapon/dagger", ([
            "armor_vs_lightning": 25,
            "attack": 20,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "armor_vs_lightning": 25,
            "attack": 20,
        ]));
    }
    setup();
}
