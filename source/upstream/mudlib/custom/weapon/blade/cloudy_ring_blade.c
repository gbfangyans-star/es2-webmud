/* 紫雲朱寰 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若這把刀還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_BLADE;

void create()
{
    set_name("\x1b[1;35m紫雲朱寰\x1b[m", ({ "cloudy ring blade", "blade" }));
    set_weight(12000);
    init_damage(4, 19, 140, 8, "blade");

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 75000);
        set("long",
            "一把通體暗紫的長刀，刀柄用鑌鐵鑲著一個用手摀住眼睛的小鬼。護手\n"
            "鑲著五個紅色的鐵環，刀身修長，中間刻著幾個小字，可看出是四個狂\n"
            "草：斃鬼殺魔。\n");
        set("apply_weapon/blade", ([
            "intimidate": 40,
            "cor": 3,
        ]));
    }
    setup();
}
