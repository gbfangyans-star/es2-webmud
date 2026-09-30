/* 玄烏杖 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("玄烏杖", ({ "stange-copper staff", "staff" }));
    set_weight(17300);
    init_damage(4, 13, 150, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 65000);
        set("long",
            "一根烏黑色的長杖，杖身似乎有一條血紅色的印記，也許是因為\n"
            "鑄杖人用自己的鮮血鑄杖而留下的。令人驚訝的是，玄烏杖竟然\n"
            "輕得出奇。\n");
        set("apply_weapon/twohanded staff", ([
            "defense": 20,
            "parry": 20,
        ]));
    }
    setup();
}
