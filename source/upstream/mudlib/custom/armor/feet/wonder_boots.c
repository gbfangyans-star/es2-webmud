/* 六合玲瓏靴 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一件；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_FEET_EQ;

void create()
{
    set_name("\x1b[1;37m六合玲瓏靴\x1b[m", ({ "wonder boots", "boots" }));
    set_weight(1000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 70000);
        set("long",
            "一雙兔毛內襯極其舒適之長筒靴子，鞋面經特殊處理具不錯的防護力。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "dex": 3,
            "dodge": 5,
            "armor": 5,
        ]));
    }
    setup();
}
