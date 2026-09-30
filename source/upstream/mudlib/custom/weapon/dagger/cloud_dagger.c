/* 幽雲短匕 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("幽雲短匕", ({ "cloud dagger", "dagger" }));
    set_weight(7600);
    init_damage(3, 15, 80, 7, "dagger");
    init_damage(3, 15, 80, 7, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 4000);
        set("long",
            "一把以百煉精鋼淬以寒鐵所打造而成的匕首，輕巧靈動，銀白的\n"
            "匕身上繪有奇異的紋飾。\n");
        set("apply_weapon/dagger", ([
            "damage": 5,
            "dex": 1,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "damage": 5,
            "dex": 1,
        ]));
    }
    setup();
}
