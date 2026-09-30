/* 符紙咒傘 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("符紙咒傘", ({ "incantation umbrella", "staff" }));
    set_weight(12000);
    init_damage(3, 12, 135, 0, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 10000);
        set("long",
            "這把符紙咒傘看起來跟一般遮陽避雨外的油紙傘沒什麼分別，但它卻是\n"
            "用了一百四十七張先天符，七十二正陽符及七十二張少陰符組製而成的\n"
            "，當中有七七四十九條以一百一十九張先天符製成的傘骨為骨架，二十\n"
            "一張先天符為傘柄, 七張先天符為傘頭，再以七十二正陽符作為傘的外\n"
            "層及七十二張少陰符作為傘的內層。加上術士灌注了咒力，使其能護佑\n"
            "棲息於其中的靈魂。\n");
        set("apply_weapon/twohanded staff", ([
            "chivi sutra": 10,
            "defense": 30,
            "wis": 2,
            "cps": 2,
        ]));
    }
    setup();
}
