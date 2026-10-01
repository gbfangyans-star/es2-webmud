/* 黑鐵大槌 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("黑鐵大槌", ({ "black iron hammer", "blunt" }));
    set_weight(41000);
    init_damage(6, 28, 135, 10, "twohanded blunt");

    if( !clonep() ) {
        set("wield_as", "twohanded blunt");
        set("unit", "把");
        set("value", 5000);
        set("long",
            "一把黑黝黝的大鐵槌，雖然看起來很笨重，但是被這麼重的武器哪怕只是\n"
            "被輕輕掃到一下也會皮開肉綻的。\n");
        set("apply_weapon/twohanded blunt", ([
            "str": 2,
            "move": -50,
            "damage": 30,
        ]));
    }
    setup();
}
