/* 射日長槍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_PIKE;

void create()
{
    set_name("\x1b[1;37m射日長槍\x1b[m", ({ "solar pike", "pike" }));
    set_weight(23000);
    init_damage(4, 20, 150, 10, "twohanded pike");

    if( !clonep() ) {
        set("wield_as", "twohanded pike");
        set("unit", "把");
        set("value", 70000);
        set("long",
            "一把閃耀著金黃色光芒的長槍，槍尖不時流動著金黃色的光暈。\n");
        set("apply_weapon/twohanded pike", ([
            "con": 4,
            "dex": -2,
            "spi": -2,
        ]));
    }
    setup();
}
