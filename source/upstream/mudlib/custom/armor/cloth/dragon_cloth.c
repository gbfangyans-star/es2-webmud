/* 蟠龍朝服 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;31m蟠龍朝服\x1b[m", ({ "dragon cloth", "cloth" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 20000);
        set("long",
            "大紅色的朝服，上頭繡著黑色的蟠龍圖案。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "awarness": 10,
            "armor": 5,
        ]));
    }
    setup();
}
