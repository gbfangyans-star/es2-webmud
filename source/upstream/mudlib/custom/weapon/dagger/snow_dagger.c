/* 雪魂匕 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("\x1b[1;31m雪魂匕\x1b[m", ({ "snow dagger", "dagger" }));
    set_weight(7600);
    init_damage(3, 15, 80, 7, "dagger");
    init_damage(3, 15, 80, 7, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 60000);
        set("long",
            "一把雕工精美，刀刃不斷閃耀著光芒的匕首。\n");
        set("apply_weapon/dagger", ([
            "con": 2,
            "cor": 1,
            "armor_vs_ice": 30,
            "attack": 5,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "con": 2,
            "cor": 1,
            "armor_vs_ice": 30,
            "attack": 5,
        ]));
    }
    setup();
}
