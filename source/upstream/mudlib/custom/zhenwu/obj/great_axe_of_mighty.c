#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("萬夫莫敵", ({ "great axe of mighty", "great axe", "mighty axe", "great", "mighty", "axe" }));
    set_weight(15000);
    setup_axe(3, 20, 113, 8);

    if( !clonep() ) {
        set("unit", "把");
        set("value", 12000);
        set("long",
            "一把閃閃發亮的精鋼巨斧，拿在手裡極其沉重，若非膂力過人，恐怕揮不動這\n"
            "把號稱「萬夫莫敵」的重兵器。\n");
        set("wield_as", "twohanded axe");
        set("apply_weapon/twohanded axe", ([
            "str": 4,
            "intimidate": -20,
        ]));
    }

    setup();
}
