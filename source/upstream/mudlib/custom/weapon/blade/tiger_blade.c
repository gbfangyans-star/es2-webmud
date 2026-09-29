/* 虎紋刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若這把刀還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_BLADE;

void create()
{
    set_name("\x1b[1;33m虎紋刀\x1b[m", ({ "tiger blade", "blade" }));
    set_weight(19400);
    init_damage(4, 17, 172, 4, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 65000);
        set("long",
            "一柄薄刃厚背的沉重大刀，刀刃上有著數條奇怪的黑紋，遠看就似老虎\n"
            "身上的虎紋。此刀正是昔年虎刀門名鎮江湖的鎮門寶刀，與瘋虎刀法同\n"
            "時施展具有極強大的破壞力，然自從此刀被盜之後下落一直不明，或者\n"
            "是見過此刀的人多半已不在人世了吧。\n");
        set("apply_weapon/twohanded blade", ([
            "cor": 2,
            "twohanded blade": 10,
            "attack": 10,
        ]));
    }
    setup();
}
