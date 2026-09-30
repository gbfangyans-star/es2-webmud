/* 萬年雪 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("\x1b[1;37m萬年雪\x1b[m", ({ "staff of ancient snow", "staff" }));
    set_weight(11200);
    init_damage(2, 16, 135, 0, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 6500);
        set("long",
            "在遙遠的北國﹐有一位法師﹐為了追求頂級的法術﹐他竟然用他未\n"
            "婚妻的身軀和鮮血打造了一把杖。這個女孩臨死的時候對他說﹕我\n"
            "不恨你﹐但是我詛咒這世界變成無盡的冬夜。終於﹐這位法師獲得\n"
            "了無盡的法力﹐但是他無法控制這種法力。在他的咒語聲中﹐不僅\n"
            "他的敵人﹐整個城鎮都被冰雪掩埋 ...... 女孩不恨他﹐他也成了\n"
            "唯一的生存者﹐活在無盡的痛苦之中﹐活在無法逃離的冰雪世界。\n");
        set("apply_weapon/twohanded staff", ([
            "wis": 2,
            "twohanded staff": 20,
            "armor_vs_ice": 100,
        ]));
    }
    setup();
}
