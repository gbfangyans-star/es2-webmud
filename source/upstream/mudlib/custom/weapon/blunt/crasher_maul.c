/* 碎腦鎚 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("碎腦鎚", ({ "crasher maul", "blunt" }));
    set_weight(22400);
    init_damage(6, 13, 160, 9, "twohanded blunt");

    if( !clonep() ) {
        set("wield_as", "twohanded blunt");
        set("unit", "把");
        set("value", 80000);
        set("long",
            "一把非常非常重的大鎚子﹐對大部份人來說﹐不要說揮動﹐連拿都拿不起來。\n"
            "如果被這麼中的鎚子雜在頭上﹐頭骨一定會被砸個粉碎。這也是這把鎚子的名\n"
            "子 — 碎腦的來歷。\n");
        set("apply_weapon/twohanded blunt", ([
            "str": 2,
            "damage": 10,
            "powerblow": 5,
        ]));
    }
    setup();
}
