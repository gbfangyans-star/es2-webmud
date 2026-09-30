/* 天龍珠 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;36m天龍珠\x1b[m", ({ "rain dragon ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 150000);
        set("long",
            "這枚看似不起眼的藍色小珠子是在天龍體內凝聚多年而成的。不僅可以驅寒\n"
            "防風，更可以使攜帶者刀劍難傷。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor_vs_wind": 50,
            "wittiness": 50,
            "armor": 20,
            "dex": 2,
            "armor_vs_ice": 50,
        ]));
    }
    setup();
}
