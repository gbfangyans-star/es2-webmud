/* 砍馬大刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("砍馬大刀", ({ "horse-twohanded blade", "blade" }));
    set_weight(12000);
    init_damage(2, 18, 105, 0, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 70000);
        set("long",
            "一把三尺長的砍馬大刀, 看起來重量頗為驚人!\n");
        set("apply_weapon/twohanded blade", ([
            "str": 2,
        ]));
    }
    setup();
}
