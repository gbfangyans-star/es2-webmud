/* 穿心刺 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("穿心刺", ({ "dagger" }));
    set_weight(5700);
    init_damage(2, 15, 100, 8, "dagger");
    init_damage(2, 15, 100, 8, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 2000);
        set("long",
            "一把鋒利的短匕首﹐是樣不錯的近身肉搏用兵器\n");
        set("apply_weapon/dagger", ([
            "cor": 1,
            "damage": 5,
            "attack": 10,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "cor": 1,
            "damage": 5,
            "attack": 10,
        ]));
    }
    setup();
}
