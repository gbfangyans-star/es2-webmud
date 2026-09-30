/* 蠻龍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_SWORD;

void create()
{
    set_name("\x1b[0;33m蠻龍\x1b[m", ({ "sword of mighty dragon", "sword" }));
    set_weight(21200);
    init_damage(4, 19, 160, 5, "twohanded sword");

    if( !clonep() ) {
        set("wield_as", "twohanded sword");
        set("unit", "把");
        set("value", 25000);
        set("long",
            "此劍劍同其名﹐蠻而無巧勁﹐使用者若非天生神力絕對沒有辦法\n"
            "發揮出此劍開山斷日之霸道氣勁。\n");
        set("apply_weapon/twohanded sword", ([
            "damage": 10,
            "armor": 10,
            "force": 5,
        ]));
    }
    setup();
}
