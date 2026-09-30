/* 天羅雲翳 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;34m天羅雲翳\x1b[m", ({ "sky cloud mail", "mail" }));
    set_weight(3000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 60000);
        set("long",
            "一件通體蔚藍，質輕而柔軟的的鎧甲，甲冑的質料非鐵非革，柔\n"
            "韌而貼身，能將內勁消弭於無形\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "cps": 2,
            "armor": 25,
            "defense": 20,
        ]));
    }
    setup();
}
