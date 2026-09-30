/* 獸皮圍裙 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("獸皮圍裙", ({ "fur sarong", "sarong" }));
    set_weight(4000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 25000);
        set("long",
            "一件不知道是狼皮還是什麼皮作成的圍裙，還帶著臭味。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "wis": -2,
            "con": 1,
            "armor": 5,
        ]));
    }
    setup();
}
