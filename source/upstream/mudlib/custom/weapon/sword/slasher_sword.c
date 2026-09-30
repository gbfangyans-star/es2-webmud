/* 繞指柔劍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("\x1b[1;37m繞指柔劍\x1b[m", ({ "slasher sword", "sword" }));
    set_weight(3300);
    init_damage(2, 10, 50, 1, "sword");

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 75000);
        set("long",
            "一把又細又長的劍﹐拿在手上劍刃就不斷抖動﹐看來要使用這把劍得要\n"
            "相當敏捷的身手才不會誤傷自己。\n");
        set("apply_weapon/sword", ([
            "intimidate": 20,
            "dex": 2,
        ]));
    }
    setup();
}
