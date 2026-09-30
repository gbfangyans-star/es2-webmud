/* 黃銅戰矛 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("黃銅戰矛", ({ "war lance", "pike" }));
    set_weight(17100);
    init_damage(4, 14, 90, 5, "twohanded pike");

    if( !clonep() ) {
        set("wield_as", "twohanded pike");
        set("unit", "把");
        set("value", 20000);
        set("long",
            "一把用黃銅打造的長矛，沒有一定膂力大的人是無法發揮其威力的。\n");
    }
    setup();
}
