/* 太乙七絕　戒 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("太乙七絕　戒", ({ "yimo ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 90000);
        set("long",
            "一枚道家煉丹所戴的防熱小戒, 你發現指環內面刻著「褰紹衣」三個小字。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "taoism-fire": 3,
            "armor_vs_fire": 20,
            "str": -1,
        ]));
    }
    setup();
}
