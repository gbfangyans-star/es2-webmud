/* 重劍龍吟 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;30m重劍\x1b[1;36m龍吟\x1b[m", ({ "dragon sword", "sword" }));
    set_weight(17900);
    init_damage(4, 15, 86, 5, "twohanded sword");

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 65000);
        set("long",
            "一把玄鐵鑄成的大劍，通體皆墨但隱隱映出湛藍劍芒，劍上金絲鐫\n"
            "著龍吟兩字，劍身奇重但握在手中頓時膽氣豪生。\n");
        set("apply_weapon/twohanded sword", ([
            "cor": 2,
            "armor": 25,
            "str": 2,
        ]));
    }
    setup();
}
