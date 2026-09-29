/* 玄鐵斬崩刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("玄鐵斬崩刀", ({ "blade of strange-iron", "blade" }));
    set_weight(8300);
    init_damage(4, 14, 110, 1, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 25000);
        set("long",
            "一把透著奇異金屬光澤的斬崩單刀。\n");
        set("apply_weapon/blade", ([
            "cor": 2,
            "seven_blade": 20,
            "parry": -15,
        ]));
    }
    setup();
}
