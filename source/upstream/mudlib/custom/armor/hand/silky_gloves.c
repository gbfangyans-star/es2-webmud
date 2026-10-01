/* 青絲手套 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("青絲手套", ({ "silky gloves", "gloves" }));
    set_weight(200);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 23000);
        set("long",
            "一副用柔軟的青絲織成的手套，非常適合優雅的女性。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "cps": 2,
            "magic": 5,
            "spells": 5,
        ]));
    }
    setup();
}
