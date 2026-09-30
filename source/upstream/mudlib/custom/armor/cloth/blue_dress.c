/* 藍鏤衣 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("藍鏤衣", ({ "blue dress", "dress" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 30000);
        set("long",
            "一件從古墓盜來的鏤衣，其散發出一種懾人的陰氣。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "cor": -2,
            "spi": 2,
        ]));
    }
    setup();
}
