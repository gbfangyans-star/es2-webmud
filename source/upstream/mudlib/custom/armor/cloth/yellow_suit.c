/* 黃短衫 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("黃短衫", ({ "yellow suit", "suit" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 4500);
        set("long",
            "一件杏黃色的無袖短衫，胸前兩條黑索交錯穿過衣孔，雖然防護力\n"
            "略遜，但穿在體魄威武之人身上，更突顯其結實勇武之勢。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "defense": 3,
            "armor": 3,
        ]));
    }
    setup();
}
