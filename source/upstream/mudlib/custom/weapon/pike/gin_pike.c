/* 紫金鳳頭錐 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("\x1b[0;34m紫金鳳頭錐\x1b[0m", ({ "gin pike", "pike" }));
    set_weight(7900);
    init_damage(4, 11, 100, 10, "pike");
    init_damage(4, 11, 100, 10, "secondhand pike");

    if( !clonep() ) {
        set("wield_as", ({ "pike", "secondhand pike" }));
        set("unit", "把");
        set("value", 5000);
        set("long",
            "一把隱隱透露出天青色的紫金短槍, 江湖上傳聞攬天門門主公孫彥\n"
            "三十年前對太湖雙惡一役便是一把太皇弓, 一枝紫金鳳頭錐重創了\n"
            "徐小惡, 更一舉巧殺白常惡! 從此紫金鳳頭錐便成江湖美談, 充滿\n"
            "了非常神秘的色彩。\n");
    }
    setup();
}

// 原資料「劇毒」：命中並造成傷害時上毒（見 daemon/condition/phoenix_poison.c）。
void hit_ob(object me, object victim, int damage)
{
    if( victim->query("life_form") == "ghost" ) return;
    CONDITION_D("phoenix_poison")->poison(victim, me);
}
