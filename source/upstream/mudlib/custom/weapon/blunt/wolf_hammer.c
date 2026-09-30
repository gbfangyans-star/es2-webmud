/* 狼牙棒 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("狼牙棒", ({ "wolf hammer", "blunt" }));
    set_weight(26700);
    init_damage(4, 26, 127, 4, "twohanded blunt");

    if( !clonep() ) {
        set("wield_as", "twohanded blunt");
        set("unit", "把");
        set("value", 45000);
        set("long",
            "一把釘了很多倒刺的大棒槌，若被這兵器擊中看來非死既傷。\n");
    }
    setup();
}
