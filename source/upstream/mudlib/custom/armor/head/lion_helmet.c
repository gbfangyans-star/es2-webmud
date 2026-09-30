/* 獅吞獸面盔 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一件；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_HEAD_EQ;

void create()
{
    set_name("\x1b[1;31m獅吞獸面盔\x1b[m", ({ "lion helmet", "helmet" }));
    set_weight(2000);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 50000);
        set("long",
            "一頂雕著獅頭的鋼盔, 獅頭睜獰, 獅眼血紅, 似乎染上的鮮血未乾, 凝結其上, 令人\n"
            "血脈噴張, 是振武指揮官的武勳, 為天邪諸侯 於蘭異 贈與米將軍之物, 代表於蘭氏\n"
            "對其之敬重與體恤。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "cor": 2,
            "armor": 15,
        ]));
    }
    setup();
}
