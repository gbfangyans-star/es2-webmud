/* 金蛇劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("金蛇劍", ({ "snake sword", "sword" }));
    set_weight(7200);
    init_damage(3, 15, 100, 4, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 12000);
        set("long",
            "一把泛著金色光芒的長劍, 劍身的尖端分叉為二, 好像蛇吐信一般\n"
            ", 真是罕見的兵器。\n");
        set("apply_weapon/sword", ([
            "awarness": 50,
            "cor": 2,
        ]));
    }
    setup();
}
