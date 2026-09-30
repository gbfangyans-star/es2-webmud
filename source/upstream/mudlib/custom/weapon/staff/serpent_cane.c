/* 冥魔杖 — ES2 原始武器資料。所屬 NPC 另行設定。 */
#include <ansi.h>
#include <weapon.h>

// 唯一性：世上（玩家身上、容器、地上、當鋪）只會有一把；NPC 重生時
// 若它還在，NPC 就不會拿到，也沒有替代品。
inherit F_UNIQUE;
inherit F_STAFF;

// 原資料「殺孽越重，特攻越多」：攻擊被閃躲或格擋時有 30% 機率發動特攻，
// 不經任何防禦直接扣對方的氣：(10 + (膽識 + 膂力) / 3) x (1 + 10% x 殺人數)。
// 殺人數用 PK 紀錄 pk_record（adm/daemons/chard.c）。

void create()
{
    set_name("\x1b[1;37m冥魔杖\x1b[m", ({ "serpent cane", "staff" }));
    set_weight(19000);
    init_damage(4, 15, 202, 10, "twohanded staff");

    if( !clonep() ) {
        set("wield_as", "twohanded staff");
        set("unit", "把");
        set("value", 85000);
        set("long",
            "一根顏色暗淡但是卻散發出妖異的黑色光澤的重杖。\n");
        set("apply_weapon/twohanded staff", ([
            "armor": 30,
            "damage": 5,
            "force": 10,
        ]));
    }
    setup();
}

// 由 combatd 在武器攻擊被閃躲或格擋後呼叫。
void miss_ob(object me, object victim)
{
    int damage;

    if( random(100) >= 30 ) return;
    damage = (10 + (me->query_attr("cor") + me->query_attr("str")) / 3)
        * (10 + me->query("pk_record")) / 10;
    message_vision(HIR "冥魔杖上的蛇頭突然睜開雙眼，一股血腥之氣直撲$n而去！\n" NOR, me, victim);
    victim->consume_stat("kee", damage, me);
}
