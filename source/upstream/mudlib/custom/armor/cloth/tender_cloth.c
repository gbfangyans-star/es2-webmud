/* 絲綢小服 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("絲綢小服", ({ "tender cloth", "cloth" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 3000);
        set("long",
            "一件很貼身的絲綢衣, 上面隱隱散發著上官小翠處女幽香。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 3,
            "dodge": 2,
        ]));
    }
    setup();
}
