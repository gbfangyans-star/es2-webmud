/* 辟雷鞭 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_WHIP;

void create()
{
    set_name("辟雷鞭", ({ "whip" }));
    set_weight(7300);
    init_damage(3, 14, 85, 8, "whip");

    if( !clonep() ) {
        set("wield_as", "whip");
        set("unit", "把");
        set("value", 15000);
        set("long",
            "一條長達六丈的長鞭, 鞭子表面黑黝黝的, 前端有著倒刺,\n"
            "看起來威力非常強大.\n");
        set("apply_weapon/whip", ([
            "cps": 1,
            "armor_vs_lightning": 50,
        ]));
    }
    setup();
}
