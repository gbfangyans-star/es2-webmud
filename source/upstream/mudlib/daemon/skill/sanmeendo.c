/*---
description: 三門刀法（NEW 新版武功寫法）。虎刀門入門刀法，設計見
             docs/martial_arts/sanmeendo_三門刀法.md，強度見 武功強度設定表.xlsx。
---*/
#include <ansi.h>

inherit "/std/martial_art";

private void create()
{
    seteuid(getuid());

    art_id    = "sanmeendo";
    art_name  = "三門刀法";
    art_usage = "blade";
    art_desc  = "虎刀門入門刀法。刀路分中、側、反三門，招式樸實、易學易練，"
                + "威力雖然平平，卻是打熬根基的好功夫。搭配狻猊步法，往往能在連續命中"
                + "對手後還能一鼓作氣再走一遍三門，故名「三門刀法」。";
    art_bonus = 0;

    moves = ({
        ([ "name": "開門見山", "lvl": 0, "attack": 8, "defense": 3, "force": 0, "bonus": 0,
           "action": "$N踏前一步﹐使出「開門見山」﹐$w當頭劈向$n的$l" ]),
        ([ "name": "迴門藏鋒", "lvl": 0, "attack": 6, "defense": 5, "force": 0, "bonus": 0,
           "action": "$N刀貼腰側一轉﹐「迴門藏鋒」﹐$w自旁翻出削向$n的$l" ]),
        ([ "name": "側門截勢", "lvl": 5, "attack": 7, "defense": 4, "force": 1, "bonus": 0,
           "action": "$N腳下一錯﹐「側門截勢」﹐$w斜斜截向$n的$l" ]),
        ([ "name": "中門直進", "lvl": 10, "attack": 9, "defense": 2, "force": 1, "bonus": 5,
           "action": "$N沉肩直進﹐「中門直進」﹐$w迎面斬向$n的$l" ]),
        ([ "name": "反門回刃", "lvl": 20, "attack": 6, "defense": 6, "force": 1, "bonus": 0,
           "action": "$N退步回身﹐「反門回刃」﹐$w反手捲向$n的$l" ]),
    });

    ma_coef  = 10;
    mm_start = 30;
    mm_minus = 11;
    mm_coef  = 10;
    mm_first_msg = "你將三門刀法反覆演練﹐漸漸體會到「攻守之間﹐門戶自分」的道理﹐\n"
                   + "對武學之道有了初步的領悟﹗\n";

    DAEMON_D->register_skill_daemon("sanmeendo");
    setup();
}

/* 三門齊開：立即把剛才連中的三招再使一遍。必中（不被閃躲、格擋，防具照樣減傷），
 * 傷害為該招平常的 75%。先列出三招，再列出每一刀後對方的體力狀態。 */
private void three_gates(object me, object opponent, object weapon, mapping *list)
{
    mapping m, act;
    int *ratios = ({}), max, r;

    message_vision(HIY "$N三刀接連得手﹐刀勢不停﹐將方才三招一氣呵成﹐再使一遍﹗\n" NOR,
        me, opponent);

    foreach(m in list) {
        if( !objectp(opponent) || environment(opponent) != environment(me) ) break;
        act = make_action(m, 75);
        act["must_hit"] = 1;
        act["brief"] = 1;
        COMBAT_D->fight(me, opponent, art_id, act, weapon);
        if( !objectp(opponent) ) break;
        max = opponent->query_stat_maximum("kee");
        if( max ) ratios += ({ opponent->query_stat("kee") * 100 / max });
    }

    if( objectp(opponent) )
        foreach(r in ratios) message_vision(COMBAT_D->status_msg(r), opponent);
}

/* 連中紀錄：最近三招都造成傷害時判定一次（往後滑）；沒中就歸零。
 * 需要三門刀法 100 級，輕功 enable 狻猊步法 60 級。
 * 機率 10% + 天生膽識 ÷ 4。發動後歸零。重演的三招不經過這裡，不算連中。 */
void after_strike(object me, object opponent, object weapon, mapping m, int damage)
{
    mixed streak;

    if( damage <= 0 ) {
        me->delete_temp("sanmeendo/streak");
        return;
    }

    streak = me->query_temp("sanmeendo/streak");
    if( !arrayp(streak) ) streak = ({});
    streak += ({ m });
    if( sizeof(streak) > 3 ) streak = streak[sizeof(streak)-3..];
    me->set_temp("sanmeendo/streak", streak);

    if( sizeof(streak) < 3 ) return;
    if( me->query_skill("sanmeendo", 1) < 100 ) return;
    if( me->skill_mapped("dodge") != "tiger-steps"
    ||  me->query_skill("tiger-steps", 1) < 60 ) return;
    if( random(100) >= 10 + me->query_attr("cor", 1) / 4 ) return;

    me->delete_temp("sanmeendo/streak");
    three_gates(me, opponent, weapon, streak);
}
