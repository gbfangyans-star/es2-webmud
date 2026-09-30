/* 陰判官袍 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("陰判官袍", ({ "judge robe", "robe" }));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 30000);
        set("long",
            "這是一件陰間判官所穿的公服，素黑的布面上沒有任何花樣﹐相當\n"
            "樸素。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "wis": 1,
            "spell": 10,
        ]));
    }
    setup();
}
