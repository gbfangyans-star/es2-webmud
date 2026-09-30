/* 罡羅環 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("\x1b[1;31m罡羅環\x1b[m", ({ "dipper necklace", "necklace" }));
    set_weight(800);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 25000);
        set("long",
            "一條由十三顆猶如拳頭般大小的黑鐵顆粒串成的鍊圈，不但烏黑，且甚\n"
            "是沉重，戴著會使人有種難以形容的安全感。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "wis": 1,
            "absorption": 5,
        ]));
    }
    setup();
}
