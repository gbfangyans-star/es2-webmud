/* 蝶舞 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("蝶舞", ({ "butterfly kris", "blade" }));
    set_weight(4000);
    init_damage(2, 13, 80, 0, "blade");
    init_damage(2, 13, 80, 0, "secondhand blade");

    if( !clonep() ) {
        set("wield_as", ({ "blade", "secondhand blade" }));
        set("unit", "把");
        set("value", 10000);
        set("long",
            "一把色彩艷麗的短刀，揮舞起來絢麗的刀光如彩蝶紛飛，因此而得名!\n");
        set("apply_weapon/blade", ([
            "dodge": 20,
            "dex": 2,
        ]));
        set("apply_weapon/secondhand blade", ([
            "dodge": 20,
            "dex": 2,
        ]));
    }
    setup();
}
