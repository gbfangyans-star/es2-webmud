/* 鬼頭劈象刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[0;33m鬼頭劈象刀\x1b[m", ({ "ghost blade", "blade" }));
    set_weight(30000);
    init_damage(4, 30, 195, 4, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 60000);
        set("long",
            "此把大刀為霸牙獅鬼將的成名兵器, 刀長七尺有餘,\n"
            "刀重九十七斤, 揮將起來, 虎虎生風, 破壞力十足。\n");
        set("apply_weapon/twohanded blade", ([
            "damage": 15,
            "str": 3,
        ]));
    }
    setup();
}
