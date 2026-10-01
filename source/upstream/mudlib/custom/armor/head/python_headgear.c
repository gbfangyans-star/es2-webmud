/* 玉蟒頭巾 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("玉蟒頭巾", ({ "python headgear", "headgear" }));
    set_weight(300);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 22000);
        set("long",
            "取青蟒鱗皮製成的頭巾，韌性極佳，觸之冷若冰雪，卻又如羽般輕柔。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "spi": 1,
            "int": 1,
            "move": 25,
        ]));
    }
    setup();
}
