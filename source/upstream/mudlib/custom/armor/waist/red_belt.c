/* 赤煌靈索 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("赤煌靈索", ({ "red belt", "belt" }));
    set_weight(300);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 10000);
        set("long",
            "一條紅色的腰帶，柔潤而輕靈，相傳具有靈性的異獸身亡時，會\n"
            "將靈力聚於體內，形成可遇而不可求的珍品。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "armor": 5,
            "maoshan-illusion": 10,
        ]));
    }
    setup();
}
