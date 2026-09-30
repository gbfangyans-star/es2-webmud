/* 赤龍筋 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_WHIP;

void create()
{
    set_name("赤龍筋", ({ "brimstony whip", "whip" }));
    set_weight(6300);
    init_damage(3, 12, 100, 7, "whip");

    if( !clonep() ) {
        set("wield_as", "whip");
        set("unit", "把");
        set("value", 5000);
        set("long",
            "這是一條龍的筋﹐擁有極好的韌性﹐也許可以當鞭子用。\n");
        set("apply_weapon/whip", ([
            "spells": 5,
            "spell": 10,
            "taoism-fire": 5,
        ]));
    }
    setup();
}
