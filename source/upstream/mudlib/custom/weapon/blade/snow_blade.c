/* 啐雪大刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;37m啐雪大刀\x1b[m", ({ "snow blade", "blade" }));
    set_weight(15900);
    init_damage(3, 17, 135, 4, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 70000);
        set("long",
            "一把通體雪白，寒氣逼人的長刀，拿在手上出乎意料的沉重。\n");
        set("apply_weapon/twohanded blade", ([
            "parry": 15,
            "intimidate": 30,
        ]));
    }
    setup();
}
