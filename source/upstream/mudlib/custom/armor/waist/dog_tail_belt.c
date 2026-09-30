/* 獒尾帶 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("獒尾帶", ({ "dog tail belt", "belt" }));
    set_weight(1000);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 10000);
        set("long",
            "怎麼看都是一條狗尾巴......\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "con": 1,
            "armor_vs_ice": 15,
        ]));
    }
    setup();
}
