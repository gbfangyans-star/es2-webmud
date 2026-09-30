/* 冷雪手護 — ES2 原始護具資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("\x1b[1;37m冷雪手護\x1b[m", ({ "snowy bracers", "bracers" }));
    set_weight(200);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 10000);
        set("long",
            "銀白色的護腕上繡了一枝梅花﹐看起來做工相當精細。由于是用絲綢製作的原\n"
            "因﹐雖然十分輕便靈活﹐防禦能力卻很差。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "intimidate": 5,
            "secondhand sword": 10,
            "sword": 10,
        ]));
    }
    setup();
}
