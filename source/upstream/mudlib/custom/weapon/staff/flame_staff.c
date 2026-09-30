/* 焚之魔杖 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("\x1b[1;31m焚之魔杖\x1b[m", ({ "flame staff", "staff" }));
    set_weight(2500);
    init_damage(2, 6, 40, 3, "staff");
    init_damage(3, 9, 60, 3, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", ({ "staff", "twohanded staff" }));
        set("unit", "把");
        set("value", 30000);
        set("long",
            "這是一把精巧的魔杖，凹凸不平的杖身使其看起來更像是一\n"
            "巨大的鑰匙。\n");
        set("apply_weapon/staff", ([
            "wis": 2,
            "spell": 30,
        ]));
        set("apply_weapon/twohanded staff", ([
            "wis": 3,
            "spell": 50,
        ]));
    }
    setup();
}
