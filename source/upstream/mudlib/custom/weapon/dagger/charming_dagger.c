/* 麗光短刃 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("\x1b[1;31m麗光短刃\x1b[m", ({ "charming dagger", "dagger" }));
    set_weight(6300);
    init_damage(3, 12, 75, 7, "dagger");
    init_damage(3, 12, 75, 7, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 7300);
        set("long",
            "這把短刃不停的散發出柔和的光輝﹐仿彿是夜裡的一點燭光﹐使人感到\n"
            "十分的溫暖﹐幾乎不忍心用它去傷害他人。\n");
        set("apply_weapon/dagger", ([
            "throwing": 5,
            "killerhood": 5,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "throwing": 5,
            "killerhood": 5,
        ]));
    }
    setup();
}
