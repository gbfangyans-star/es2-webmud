/* 封印雷環 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("\x1b[1;33m封印雷環\x1b[m", ({ "thunder ring", "ring" }));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 100000);
        set("long",
            "一百五十多年前白象禪院高僧莫悲大師在兆隱縣外密林之中巧遇一獸，亦熊\n"
            "亦虎體大如象。莫悲大師見此獸身有雷光隱現，知其體內必有仙物。此獸見\n"
            "莫悲大師並無恐懼之色，竟爬到莫悲大師身邊將一枚戒指吐了出來然後便伴\n"
            "著一道雷光消失的無影無蹤。莫悲大師圓寂後這枚戒指流傳到一俗家弟子手\n"
            "中，該弟子日後「瘋虎功」大成創立了「虎刀門」，而這戒指也就一起到了\n"
            "虎刀門，並由歷代掌門人保管。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "taoism-thunder": 15,
            "wis": 2,
        ]));
    }
    setup();
}
