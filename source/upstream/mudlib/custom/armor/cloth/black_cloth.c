/* 墨色布衣 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("墨色布衣", ({ "black cloth", "cloth" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 8000);
        set("long",
            "一件黑色的普通步衣, 在它右胸的部份繡了「青邪」兩字。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "attack": 3,
            "armor": 5,
        ]));
    }
    setup();
}
