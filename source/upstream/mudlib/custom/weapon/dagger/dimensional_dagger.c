/* 「旋芒」 — ES2 參考資料（es2tips 等）。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("「旋芒」", ({ "dimensional dagger", "dagger" }));
    set_weight(7600);
    init_damage(3, 15, 80, 7, "dagger");
    init_damage(3, 15, 80, 7, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 35000);
        set("long",
            "古刃『旋芒』殘餘的劍身再度重生，雖然短了不少，但是當成是\n"
            "匕首用的話，還是相當合適的。\n");
        set("apply_weapon/dagger", ([
            "intimidate": 25,
            "fire_damage": 25,
            "ice_damage": 25,
            "lightning_damage": 25,
            "damage": 50,
            "wind_damage": 25,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "intimidate": 25,
            "fire_damage": 25,
            "ice_damage": 25,
            "lightning_damage": 25,
            "damage": 50,
            "wind_damage": 25,
        ]));
    }
    setup();
}
