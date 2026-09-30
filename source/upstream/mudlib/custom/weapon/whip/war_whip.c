/* 戰鞭 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_WHIP;

void create()
{
    set_name("戰鞭", ({ "war whip", "whip" }));
    set_weight(4800);
    init_damage(3, 9, 65, 5, "whip");

    if( !clonep() ) {
        set("wield_as", "whip");
        set("unit", "把");
        set("value", 60000);
        set("long",
            "一條很少見的戰鬥用的鞭子﹐看起來很結實﹐被抽到一定 很 痛 很 痛 ∼ ∼\n");
    }
    setup();
}
