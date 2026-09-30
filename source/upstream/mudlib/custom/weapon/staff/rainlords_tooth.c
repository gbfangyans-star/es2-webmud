/* 雨神之牙 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

// 原資料註：未開光。insert／pull 與 freeze pill 效果依使用者指示不製作。

void create()
{
    set_name("\x1b[1;36m雨神之牙\x1b[m", ({ "rainlord's tooth", "staff" }));
    set_weight(21400);
    init_damage(4, 18, 225, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 80000);
        set("long",
            "這是一根尚未成形的龍牙，據說要塗過邪惡天龍的血才能成形。\n"
            "(insert tooth into corpse of Rainlord dragon)\n");
        set("apply_weapon/twohanded staff", ([
            "wis": 1,
            "armor": 10,
            "armor_vs_ice": 50,
        ]));
    }
    setup();
}
