/* 如是菩提 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("\x1b[1;33m如是菩提\x1b[m", ({ "bodhi rosary", "rosary" }));
    set_weight(200);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 15000);
        set("long",
            "一串以香木所串起的念珠，在其中央有一顆指頭般大小，晶瑩剔\n"
            "透而又微微泛著黃光的珠子，據聞是佛門中菩提舍利經由巧手妙\n"
            "匠所製成的聖物。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "wis": 1,
            "spi": 1,
            "int": 1,
        ]));
    }
    setup();
}
