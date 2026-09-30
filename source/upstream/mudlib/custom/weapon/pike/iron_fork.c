/* 鑌鐵叉 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("鑌鐵叉", ({ "iron fork", "pike" }));
    set_weight(4300);
    init_damage(2, 14, 70, 0, "pike");

    if( !clonep() ) {
        set("wield_as", "pike");
        set("unit", "把");
        set("value", 85000);
        set("long",
            "一把又長又重的鑌鐵叉﹐尖刺約有二尺來長。\n");
    }
    setup();
}
