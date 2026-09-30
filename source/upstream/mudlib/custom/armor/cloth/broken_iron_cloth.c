/* 殘鐵衣 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("殘鐵衣", ({ "broken iron cloth", "cloth" }));
    set_weight(6000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 5000);
        set("long",
            "一件笨重的青鐵衣服, 上頭是用一片片像鱗片似的生鐵打製而成。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 10,
            "parry": 5,
            "dodge": -5,
        ]));
    }
    setup();
}
