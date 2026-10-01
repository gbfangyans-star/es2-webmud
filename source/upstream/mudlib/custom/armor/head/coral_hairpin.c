/* 珊瑚髮釵 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("珊瑚髮釵", ({ "coral hairpin", "hairpin" }));
    set_weight(100);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "支");
        set("value", 26000);
        set("long",
            "一支鮮紅的珊瑚，可以用來當髮釵。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "move": 50,
            "force": 5,
            "awarness": 50,
        ]));
    }
    setup();
}
