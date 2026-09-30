/* 蛈蜇杳龍屐 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一件；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_FEET_EQ;

void create()
{
    set_name("蛈蜇杳龍屐", ({ "dragon boots", "boots" }));
    set_weight(500);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 45000);
        set("long",
            "一雙看起來手工極為輕巧的木屐, 手頭繪有雙龍圖案。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "intimidate": 30,
            "armor": 15,
            "damage": 10,
        ]));
    }
    setup();
}
