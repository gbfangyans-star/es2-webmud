/* 青綠軍袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;32m青綠軍袍\x1b[m", ({ "green suit", "suit" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 30000);
        set("long",
            "這是一件青綠色軍服．上面印焱硝軍的標誌\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "damage": 5,
            "cor": 1,
            "armor": 5,
        ]));
    }
    setup();
}
