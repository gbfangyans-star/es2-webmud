/* 天地雲衫 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;37m天地雲衫\x1b[m", ({ "sky_earth cloth", "cloth" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 50000);
        set("long",
            "一套罕見的衣裳, 上面繡有雲朵圖樣, 看起來相當華麗。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 5,
            "spell": 35,
            "taoism-taoshan": 20,
        ]));
    }
    setup();
}
