/* 黃綢汗衫 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("黃綢汗衫", ({ "yellow cloth", "cloth" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 4500);
        set("long",
            "一件緊身的黃色綢衣, 似乎有點太過鮮明 ...\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 3,
        ]));
    }
    setup();
}
