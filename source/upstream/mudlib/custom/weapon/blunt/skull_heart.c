/* 萬骨枯心 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("\x1b[1;37m萬骨枯心\x1b[m", ({ "skull heart", "blunt" }));
    set_weight(21800);
    init_damage(3, 28, 109, 0, "twohanded blunt");

    if( !clonep() ) {
        set("wield_as", "twohanded blunt");
        set("unit", "把");
        set("value", 20000);
        set("long",
            "一根雪白色的長鎚﹐上面密密麻麻的刻滿了骷髏頭。\n"
            "仔細看看﹐骷髏頭並不是刻上的﹐而是﹐這根鎚就是\n"
            "用無數的骷髏頭製成的﹗\n");
    }
    setup();
}

// 原資料「劇毒」：命中並造成傷害時上毒（見 daemon/condition/skull_heart_poison.c）。
void hit_ob(object me, object victim, int damage)
{
    if( victim->query("life_form") == "ghost" ) return;
    CONDITION_D("skull_heart_poison")->poison(victim, me);
}
