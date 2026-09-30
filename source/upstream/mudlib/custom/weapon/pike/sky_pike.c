/* 震天戢 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("\x1b[1;37m震天戢\x1b[m", ({ "sky pike", "pike" }));
    set_weight(4800);
    init_damage(3, 10, 60, 2, "pike");
    init_damage(3, 10, 60, 2, "secondhand pike");

    if( !clonep() ) {
        set("wield_as", ({ "pike", "secondhand pike" }));
        set("unit", "把");
        set("value", 20000);
        set("long",
            "一把長度約九尺, 白色戢身, 世上難得的利器。\n");
    }
    setup();
}
