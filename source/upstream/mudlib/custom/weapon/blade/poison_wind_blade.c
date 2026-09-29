/* 酖風刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;34m酖風刀\x1b[m", ({ "poison wind blade", "blade" }));
    set_weight(21400);
    init_damage(3, 26, 135, 4, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 80000);
        set("long",
            "血絕門的鎮門寶刀，長期浸泡於萬毒藥水中，刀身散發出一縷黑氣，彷彿有生命般地呼吸著。\n");
        set("apply_weapon/twohanded blade", ([
            "force": 10,
            "damage": 10,
            "awarness": 50,
        ]));
    }
    setup();
}
