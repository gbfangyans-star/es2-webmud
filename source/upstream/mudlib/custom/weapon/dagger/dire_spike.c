/* 椎心刺 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("椎心刺", ({ "dire spike", "dagger" }));
    set_weight(7600);
    init_damage(3, 15, 80, 7, "dagger");
    init_damage(3, 15, 80, 7, "secondhand dagger");

    if( !clonep() ) {
        set("wield_as", ({ "dagger", "secondhand dagger" }));
        set("unit", "把");
        set("value", 10000);
        set("long",
            "一把精鋼鑄造的短刺，上面刻著十四道用來放血的溝槽，把手上包著一條粗布用\n"
            "來防滑。\n");
        set("apply_weapon/dagger", ([
            "intimidate": 5,
            "attack": 15,
        ]));
        set("apply_weapon/secondhand dagger", ([
            "intimidate": 5,
            "attack": 15,
        ]));
    }
    setup();
}
