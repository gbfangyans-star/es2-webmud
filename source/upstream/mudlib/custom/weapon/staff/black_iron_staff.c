/* 黑鋼杖 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("黑鋼杖", ({ "black-iron staff", "staff" }));
    set_weight(2600);
    init_damage(2, 8, 90, 0, "staff");
    init_damage(3, 12, 135, 0, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", ({ "staff", "twohanded staff" }));
        set("unit", "把");
        set("value", 95000);
        set("long",
            "一根黑色的鐵杖, 看起來似乎很沉重的樣子 ...\n");
        set("apply_weapon/twohanded staff", ([
            "defense": 10,
        ]));
    }
    setup();
}
