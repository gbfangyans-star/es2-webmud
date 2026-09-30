/* 潤神幻戒 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;32m潤神幻戒\x1b[m", ({ "ring of summon", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 150000);
        set("long",
            "一枚散著誘人的綠色光芒的魔戒。相傳﹐五千年前勇士寒於借冰火風雷\n"
            "四大聖獸之力封印侮天鬼之後﹐將奄奄一息四大聖獸收入戒中﹐以保其\n"
            "肉身。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 20,
            "wis": 2,
            "armor_vs_fire": 50,
            "armor_vs_ice": 50,
            "armor_vs_wind": 50,
            "armor_vs_lightning": 50,
        ]));
    }
    setup();
}
