/* 赤龍牙骨 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("赤龍牙骨", ({ "fire-dragon tooth", "dagger" }));
    set_weight(6300);
    init_damage(3, 12, 75, 7, "dagger");
    init_damage(3, 12, 75, 7, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 5000);
        set("long",
            "這是一枚罕見的赤龍牙骨，據說持有者可以火中取物而不傷。\n");
        set("apply_weapon/dagger", ([
            "armor_vs_fire": 25,
            "cor": 1,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "armor_vs_fire": 25,
            "cor": 1,
        ]));
    }
    setup();
}
