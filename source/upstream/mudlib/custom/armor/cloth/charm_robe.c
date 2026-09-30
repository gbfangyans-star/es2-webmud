/* 仙符鏽袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("仙符鏽袍", ({ "charm robe", "robe" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 30000);
        set("long",
            "一件樣式頗為簡單的道袍，袍上寫滿了道籙天書、密宗心經等奇異的文字。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "taoism of purify": 10,
            "armor": 10,
        ]));
    }
    setup();
}
