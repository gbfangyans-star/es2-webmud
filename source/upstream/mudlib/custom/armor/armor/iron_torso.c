/* 鑌鐵胸鎧 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("鑌鐵胸鎧", ({ "iron torso", "torso" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 15000);
        set("long",
            "這件胸鎧上面綴了許多鑌鐵鎖片﹐從胸至腰。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor_vs_fire": 5,
            "armor_vs_lightning": 5,
            "armor": 12,
        ]));
    }
    setup();
}
