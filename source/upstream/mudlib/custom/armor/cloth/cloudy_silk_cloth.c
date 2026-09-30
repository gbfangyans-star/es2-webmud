/* 雲羅絲衣 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("\x1b[1;37m雲羅絲衣\x1b[m", ({ "cloudy silk cloth", "cloth" }));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 30000);
        set("long",
            "這件絲衣是用百年冰蠶的蠶絲縫製而成，所以對冰系法術有一定的\n"
            "抵抗力。整件絲衣薄如蟬翼，輕如鴻毛，做工相當精細。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 5,
            "armor_vs_ice": 10,
            "maoshan-illusion": 10,
        ]));
    }
    setup();
}
