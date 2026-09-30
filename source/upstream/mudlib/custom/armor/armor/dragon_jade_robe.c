/* 龍鱗璧玉袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;36m龍鱗璧玉袍\x1b[m", ({ "dragon armor", "armor" }));
    set_weight(5000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 20000);
        set("long",
            "一套看來相當華麗的巨大鎧甲﹐外圍相傳是用龍鱗和綠玉合製而成的﹐內部則是以相\n"
            "當輕飄的鳳凰羽編製﹐是不可多得的傳奇神器。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "taoism of dunja": 10,
            "armor_vs_fire": 20,
            "armor": 20,
            "wis": 1,
        ]));
    }
    setup();
}
