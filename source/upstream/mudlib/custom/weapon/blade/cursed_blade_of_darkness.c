/* 渾天刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;30m渾天刀\x1b[m", ({ "cursed blade of darkness", "blade" }));
    set_weight(18800);
    init_damage(3, 21, 90, 6, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 95000);
        set("long",
            "渾天刀﹐刀長六尺半刀寬三尺五﹐漆黑的刀身充滿了濃重的殺氣。\n");
        set("apply_weapon/twohanded blade", ([
            "cor": 2,
        ]));
    }
    setup();
}
