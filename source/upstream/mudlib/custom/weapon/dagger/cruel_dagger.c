/* 血刃 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("血刃", ({ "cruel dagger", "dagger" }));
    set_weight(6300);
    init_damage(3, 12, 75, 7, "dagger");
    init_damage(3, 12, 75, 7, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 85000);
        set("long",
            "一把鋒利的匕首﹐上面還有發乾了的血跡......\n");
        set("apply_weapon/dagger", ([
            "parry": 5,
            "damage": 5,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "parry": 5,
            "damage": 5,
        ]));
    }
    setup();
}
