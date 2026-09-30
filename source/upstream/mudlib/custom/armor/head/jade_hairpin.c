/* 翠玉髮簪 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("\x1b[1;32m翠玉髮簪\x1b[m", ({ "jade hairpin", "hairpin" }));
    set_weight(100);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "支");
        set("value", 10000);
        set("long",
            "一支翠玉雕刻而成的髮簪, 非富貴人家難得一見的飾品。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "spi": 1,
            "defense": 5,
        ]));
    }
    setup();
}
