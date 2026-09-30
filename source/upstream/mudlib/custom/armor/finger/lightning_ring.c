/* 雷光指環 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;33m雷光指環\x1b[m", ({ "lightning ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 90000);
        set("long",
            "一枚鍍金的指環，上面纏繞著一層耀眼的雷光。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "str": 1,
            "armor_vs_lightning": 30,
            "taoism-thunder": 5,
        ]));
    }
    setup();
}
