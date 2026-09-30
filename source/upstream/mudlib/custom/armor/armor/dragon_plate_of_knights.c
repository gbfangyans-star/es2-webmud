/* 龍騎戰甲 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("\x1b[1;33m龍騎戰甲\x1b[m", ({ "dragon plate of knights", "plate" }));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 30000);
        set("long",
            "一件厚重的鎧甲, 為軒轅心塵特地請匠師打造給領兵出爭的將軍們穿著的戰甲, 戰\n"
            "甲極為厚實, 非體格魁偉之人是無法穿戴的, 此外也因只有高階將領才會配發此甲\n"
            "所以穿著了這件龍騎甲, 在軒轅軍中也象徵了階級與地位。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "con": 2,
            "armor": 30,
            "dex": -1,
        ]));
    }
    setup();
}
