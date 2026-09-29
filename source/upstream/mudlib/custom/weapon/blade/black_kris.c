/* 黑風刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("黑風刀", ({ "black kris", "blade" }));
    set_weight(8500);
    init_damage(2, 13, 80, 0, "blade");
    init_damage(2, 6, 80, 0, "secondhand blade");

    if( !clonep() ) {
        set("wield_as", ({ "blade", "secondhand blade" }));
        set("unit", "把");
        set("value", 85000);
        set("long",
            "一把黑漆漆的短刀, 刀面上隱隱散發出一陣陣的黑氣!\n");
        set("apply_weapon/blade", ([
            "parry": 10,
            "str": 1,
        ]));
        set("apply_weapon/secondhand blade", ([
            "parry": 10,
            "str": 1,
        ]));
    }
    setup();
}
