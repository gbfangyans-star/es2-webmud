/* 飛鷹盔 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("飛鷹盔", ({ "eagle helmet", "helmet" }));
    set_weight(2000);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 25000);
        set("long",
            "一頂鑲金的頭盔，頭盔兩旁還有著雄鷹展翅的飾物，乃是將軍級的\n"
            "武官才得以擁有的戰盔。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "str": 1,
            "armor": 5,
            "defense": 5,
        ]));
    }
    setup();
}
