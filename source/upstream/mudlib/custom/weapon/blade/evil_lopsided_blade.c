/* 邪門歪刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若這把刀還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_BLADE;

void create()
{
    set_name("\x1b[1;30m邪門歪刀\x1b[m", ({ "evil-lopsided blade", "blade" }));
    set_weight(6100);
    init_damage(3, 12, 90, 5, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 85000);
        set("long",
            "一把黑沉沉，刀身盡是歪刃倒勾的細長單刀。\n"
            "你見到刀柄上刻著「邪門一刀，歪打正著」八個小字。\n");
        set("apply_weapon/blade", ([
            "parry": 10,
            "attack": 20,
        ]));
    }
    setup();
}
