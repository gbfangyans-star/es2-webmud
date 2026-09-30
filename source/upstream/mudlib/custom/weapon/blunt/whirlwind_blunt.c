/* 旋風流星槌 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("旋風流星槌", ({ "whirlwind blunt", "blunt" }));
    set_weight(26700);
    init_damage(4, 26, 127, 4, "twohanded blunt");

    if( !clonep() ) {
        set("wield_as", "twohanded blunt");
        set("unit", "把");
        set("value", 56000);
        set("long",
            "一把沉重的大銅槌﹐手柄上面還纏繞著一條青鋼鐵鏈﹐揮舞起來會發出「嘩\n"
            "嘩」的聲音。\n");
        set("apply_weapon/twohanded blunt", ([
            "berserk": 10,
            "powerblow": 10,
        ]));
    }
    setup();
}
