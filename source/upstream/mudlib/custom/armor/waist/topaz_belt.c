/* 黃玉佩 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("黃玉佩", ({ "topaz belt", "belt" }));
    set_weight(800);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 1600);
        set("long",
            "一條纏著一枚黃玉的腰帶，雖然不很值錢，但是看起來頗有品位。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "spi": 1,
            "int": 1,
        ]));
    }
    setup();
}
