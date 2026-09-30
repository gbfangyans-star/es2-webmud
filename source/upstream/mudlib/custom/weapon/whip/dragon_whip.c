/* 毒龍鞭 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_WHIP;

void create()
{
    set_name("\x1b[1;35m毒龍鞭\x1b[m", ({ "dragon whip", "whip" }));
    set_weight(6300);
    init_damage(3, 12, 100, 7, "whip");

    if( !clonep() ) {
        set("wield_as", "whip");
        set("unit", "把");
        set("value", 30000);
        set("long",
            "一條十尺半長的鞭子，柄長尺半，鞭身長九尺，上面附著一根根的倒刺\n"
            "，由於刺上帶有劇毒，要使用須有相當技巧。\n");
        set("apply_weapon/whip", ([
            "spells": 20,
            "magic": 20,
            "attack": 30,
        ]));
    }
    setup();
}
