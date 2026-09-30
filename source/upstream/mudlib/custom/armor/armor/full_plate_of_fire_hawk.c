/* 火鷹戰鎧 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一件；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;31m火鷹戰鎧\x1b[m", ({ "full plate of fire hawk", "plate" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 100000);
        set("long",
            "一件火紅色鎧甲, 胸前雕著一隻展翅的大鷹, 鷹勾褐黃, 羽毛赤紅, 似以精鋼加火\n"
            "熔岩練成，厚重堅實，為不可多得之寶甲, 只是稍嫌笨重, 非魁武者難適應。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "intimidate": 20,
            "armor": 35,
            "cor": 2,
            "armor_vs_fire": 50,
        ]));
    }
    setup();
}
