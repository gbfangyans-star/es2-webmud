/* 憤怒明王槍 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_PIKE;

void create()
{
    set_name("\x1b[1;31m憤怒明王槍\x1b[0m", ({ "wraith of warlord", "pike" }));
    set_weight(9900);
    init_damage(5, 12, 100, 9, "pike");
    init_damage(5, 12, 100, 9, "secondhand pike");

    if( !clonep() ) {
        set("wield_as", ({ "pike", "secondhand pike" }));
        set("unit", "把");
        set("value", 45000);
        set("long",
            "一把透著冷冷寒意的丈八長槍, 此槍相傳是兩百年前槍魔戚征威的佩槍, 是由\n"
            "九天女媧七彩石所煉出的神兵, 由於槍頭在煉製時加上了三色孔雀膽的汁液,\n"
            "所以含有劇毒, 是一把非常可怕的紅色魔槍。\n");
        set("apply_weapon/pike", ([
            "intimidate": 20,
            "cor": 2,
        ]));
        set("apply_weapon/secondhand pike", ([
            "intimidate": 20,
            "cor": 2,
        ]));
    }
    setup();
}

// 原資料「劇毒」：命中並造成傷害時上毒（見 daemon/condition/wraith_poison.c）。
void hit_ob(object me, object victim, int damage)
{
    if( victim->query("life_form") == "ghost" ) return;
    CONDITION_D("wraith_poison")->poison(victim, me);
}
