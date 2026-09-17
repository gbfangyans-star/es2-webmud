// /d/lee/obj/tight_cloth.c
// NEW（李家村復原版新增道具，非原始 ES2 資料，由專案成員指定數值）
// 以 obj/cloth.c（布衣，value 60、armor 1）為基礎，依需求「比布衣高級一點」：
// 賣價 x10（60 -> 600）、防禦 +3（1 -> 4）。重量沿用布衣原值，未特別要求變動。

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("緊身衣", ({ "tight cloth", "tight clothes" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 600);
        set("long", "一件剪裁貼身的獵裝衣物，行動起來比寬鬆的布衣更加俐落。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 4,
        ]));
    }

    setup();
}
