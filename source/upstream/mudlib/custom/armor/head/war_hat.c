/* 戰帽 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("戰帽", ({ "war hat", "hat" }));
    set_weight(300);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 1000);
        set("long",
            "不少江湖中人所喜愛的帽子﹐擁有不錯的防禦力的同時也十分的便宜。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "defense": 25,
            "damage": 10,
        ]));
    }
    setup();
}
