/* 霓虹采裳 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;35m霓虹采裳\x1b[m", ({ "rainbow gown", "gown" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 25000);
        set("long",
            "一件淺紅色的絲衣，摸起來柔若無物。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "spi": 1,
            "wis": 1,
            "armor": 2,
        ]));
    }
    setup();
}
