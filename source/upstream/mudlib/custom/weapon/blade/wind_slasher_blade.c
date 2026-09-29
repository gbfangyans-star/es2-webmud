/* 斬風刀 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("\x1b[1;37m斬風刀\x1b[m", ({ "wind-slasher blade", "blade" }));
    set_weight(21400);
    init_damage(3, 26, 135, 4, "twohanded blade");

    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 16000);
        set("long",
            "斬風刀是按照謝青翔的設計所打造的雙手刀。刀身背厚刃薄，極\n"
            "利於砍劈動作，彷彿連風都能斬斷一般，故名之。\n");
        set("apply_weapon/twohanded blade", ([
            "attack": 50,
            "armor_vs_wind": 50,
        ]));
    }
    setup();
}
