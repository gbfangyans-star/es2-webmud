/* 藥王神劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[0;36m藥王神劍\x1b[m", ({ "medication-king sword", "sword" }));
    set_weight(8700);
    init_damage(3, 18, 100, 6, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 100000);
        set("long",
            "藥王神劍為侮藥王鬼將的成名兵器。劍身上刻著【天下藥王, 盡為所辱】\n"
            "八個傲氣十足的楷字。\n");
        set("apply_weapon/sword", ([
            "spells": 5,
            "wis": 1,
            "spell": 10,
        ]));
    }
    setup();
}
