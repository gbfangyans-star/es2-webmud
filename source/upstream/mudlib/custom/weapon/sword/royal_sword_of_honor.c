/* 英雄王者劍 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("英雄王者劍", ({ "royal sword of honor", "royal sword", "sword" }));
    set_weight(26900);
    init_damage(4, 26, 180, 5, "twohanded sword");

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 100000);
        set("long",
            "此劍劍身金光閃閃華麗異常，劍柄處雕龍畫鳳，一看就是皇家器具。\n");
        set("apply_weapon/twohanded sword", ([
            "twohanded sword": 10,
            "force": 10,
            "attack": 30,
        ]));
    }
    setup();
}
