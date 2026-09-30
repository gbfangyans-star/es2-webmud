/* 梅花匕 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("梅花匕", ({ "lunmay dagger", "dagger" }));
    set_weight(5700);
    init_damage(2, 15, 100, 8, "dagger");
    init_damage(2, 15, 100, 8, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 65000);
        set("long",
            "一把鋒利的短匕首﹐匕首的手柄處刻有幾朵梅花和一個小小的「武」字。\n");
        set("apply_weapon/dagger", ([
            "dagger": 10,
            "damage": 5,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "dagger": 10,
            "damage": 5,
        ]));
    }
    setup();
}
