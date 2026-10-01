/* 舊銀髮簪 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("舊銀髮簪", ({ "old silver hairpin", "hairpin" }));
    set_weight(100);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "支");
        set("value", 3800);
        set("long",
            "一支看起來很舊，但是卻清理得十分乾淨的銀製髮簪，想來對李\n"
            "璐雯來說是非常重要的東西。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "spi": 1,
        ]));
    }
    setup();
}
