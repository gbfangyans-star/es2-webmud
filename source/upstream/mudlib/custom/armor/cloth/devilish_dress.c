/* 水慾羽衣 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("水慾羽衣", ({ "devilish dress", "dress" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 40000);
        set("long",
            "一件用鸂鷘的羽毛縫製而成的衣裳﹐輕柔透明不似凡間之物。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 10,
            "damage": 10,
            "sneak": 10,
        ]));
    }
    setup();
}
