/* 紅色武道衣 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("紅色武道衣", ({ "red cloth", "cloth" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 3000);
        set("long",
            "一件輕便的紅色武道衣, 它的質料似乎很不錯。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 4,
        ]));
    }
    setup();
}
