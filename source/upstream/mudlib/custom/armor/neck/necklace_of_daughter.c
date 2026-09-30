/* 龍兒鎖 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("龍兒鎖", ({ "necklace of daughter", "necklace" }));
    set_weight(200);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 15000);
        set("long",
            "一條漂亮的金項鍊﹐金項鍊的一段上若有若無的刻著一個龍字。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "wittiness": 5,
            "armor_vs_wind": 10,
        ]));
    }
    setup();
}
