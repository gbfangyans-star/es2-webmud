/* 血月斧 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_AXE;

void create()
{
    set_name("\x1b[1;31m血月斧\x1b[m", ({ "axe of bloodmoon", "axe" }));
    set_weight(6900);
    init_damage(3, 14, 100, 5, "axe");
    init_damage(3, 7, 100, 5, "secondhand axe");

    if( !clonep() ) {
        set("wield_as", ({ "axe", "secondhand axe" }));
        set("unit", "把");
        set("value", 35000);
        set("long",
            "血月斧整體以赤鐵打造，斧刃部分呈半月型。\n");
        set("apply_weapon/axe", ([
            "intimidate": 15,
            "attack": 20,
        ]));
        set("apply_weapon/secondhand axe", ([
            "intimidate": 15,
            "attack": 20,
        ]));
    }
    setup();
}
