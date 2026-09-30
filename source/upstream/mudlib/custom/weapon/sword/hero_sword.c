/* 英雄劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("英雄劍", ({ "hero sword", "sword" }));
    set_weight(3300);
    init_damage(2, 10, 50, 1, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 30000);
        set("long",
            "一把精鋼鑄成的長劍, 劍身上刻有麒麟的圖案, 劍柄約有十吋長。\n");
        set("apply_weapon/sword", ([
            "damage": 10,
            "attack": 10,
        ]));
    }
    setup();
}
