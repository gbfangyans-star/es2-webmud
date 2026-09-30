/* 易羅大劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("易羅大劍", ({ "broadsword", "sword" }));
    set_weight(13000);
    init_damage(3, 13, 106, 2, "twohanded sword");

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 60000);
        set("long",
            "為蔭百邪鬼將的兵器, 劍尖隱隱散著陣陣臭氣。\n");
        set("apply_weapon/twohanded sword", ([
            "force": 15,
        ]));
    }
    setup();
}
