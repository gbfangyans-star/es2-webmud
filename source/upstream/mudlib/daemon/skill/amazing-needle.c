/*---
description: 武陀灸術【驚異二針】（amazing-needle）。武陀灸堂方士的針法，enable 在
             針灸之術（cauterization）上，以 acupuncture 施針：
             amazing_armor（驚異霸甲針）、amazing_power（驚異霸氣針）強化目標，
             self_test 自扎試針累積經驗。
design: docs/martial_arts/武陀灸堂_門派設計.md 第四章（2026-10-27 定案）
---*/
#include <ansi.h>

inherit SKILL;

#include "/daemon/skill/wuto_needle.h"

#define SKILL_ID "amazing-needle"
#define CND      "wuto_amazing"

void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon(SKILL_ID);
    setup();
}

int valid_learn(object me) { return check_wuto(me); }

void skill_completed(object me, string skill)
{
    tell_object(me, HIY + gender_self(me) + "終於練成了驚異二針，針尖輕顫之間，"
        "已能將一身氣血催得或堅凝、或霸道。\n" NOR);
}

/* A-01、A-02：對他人的加成；A-03 對自己乘四。 */
private mapping needle_apply(string kind, int sk, int times)
{
    if( kind == "armor" )
        return ([ "armor": sk / 4 * times, "defense": sk / 5 * times,
                  "damage": sk / 20 * times, "attack": sk / 10 * times ]);
    return ([ "damage": sk / 4 * times, "attack": sk / 5 * times,
              "armor": sk / 20 * times, "defense": sk / 10 * times ]);
}

private string needle_title(string kind)
{
    return kind == "armor" ? HIY "『 驚 異 霸 甲 針 』" NOR : HIR "『 驚 異 霸 氣 針 』" NOR;
}

int do_amazing(object me, string kind, object target)
{
    mapping data;
    int sk, cost, times;

    sk = me->query_skill(SKILL_ID, 1);
    cost = 10 + sk / 5;
    if( me->query_stat("sen") < cost )
        return notify_fail(gender_self(me) + "的心神不足，捏不穩手中的針。\n");

    // A-04：霸甲、霸氣同一目標只能有一種；同一種再扎一次重新計時、以新的數值為準。
    data = target->query_condition(CND);
    if( mapp(data) && data["kind"] != kind )
        return notify_fail((target == me ? gender_self(me) : target->name())
            + "身上的" + (data["kind"] == "armor" ? "驚異霸甲針" : "驚異霸氣針")
            + "針力未散，再扎另一針只怕氣血逆衝。\n");

    me->consume_stat("sen", cost);
    times = target == me ? 4 : 1;

    // 招名字距較寬，自動換行會把它拆開，所以自己分行、不自動換行。
    if( target == me )
        message_vision((kind == "armor" ? YEL : RED)
            + "$N反手拈起一枚長針，對準自己頭頂百會穴"
            + (kind == "armor" ? "緩緩捻入，\n" : "猛然一刺，\n")
            + "正是" + needle_title(kind) + (kind == "armor" ? YEL : RED) + "！\n"
            + (kind == "armor"
                ? "$N周身筋肉一緊，皮膚隱隱泛起一層暗黃光澤，宛如披上了一重鐵甲。\n"
                : "$N雙目驟然泛紅，一股霸道之氣自頭頂直貫四肢，骨節格格作響。\n") + NOR,
            me, 0, 1);
    else
        message_vision((kind == "armor" ? YEL : RED)
            + (kind == "armor" ? "$N捏針在手，一按$n頭頂，長針應手沒入百會穴，\n"
                               : "$N捏針在手，對準$n頭頂百會穴疾刺而下，\n")
            + "正是" + needle_title(kind) + (kind == "armor" ? YEL : RED) + "！\n"
            + (kind == "armor"
                ? "$n只覺一股酸脹自頭頂沉入四肢，筋骨堅凝，彷彿刀劍難傷。\n"
                : "$n渾身一震，氣血翻湧直上，雙拳不自覺地握得格格作響。\n") + NOR,
            me, target, 1);

    set_needle_effect(target, CND, kind, needle_apply(kind, sk, times), sk);
    needle_gain(me, SKILL_ID);
    me->start_busy(1);
    return 1;
}

/* A-07：self_test，扣自己氣的可用上限 2 點，換一次悟性公式的經驗。 */
int do_self_test(object me)
{
    if( me->query_stat_effective("kee") <= 2 )
        return notify_fail(gender_self(me) + "的氣血太虛，經不起再扎了。\n");
    me->damage_stat("kee", 2, me);
    message_vision("$N拈起一枚細針，在自己臂上穴道淺淺試扎了幾下，"
        "凝神體會針下氣機的流轉。\n", me);
    needle_gain(me, SKILL_ID);
    me->start_busy(1);
    return 1;
}

varargs int acupuncture_cauterization(object me, string spl, object target)
{
    string kind;

    if( !knows_needle(me, SKILL_ID) )
        return notify_fail(gender_self(me) + "還沒學會驚異二針。\n");

    switch(spl) {
    case "amazing_armor": case "armor": case "驚異霸甲針":
        kind = "armor";
        break;
    case "amazing_power": case "power": case "驚異霸氣針":
        kind = "power";
        break;
    case "self_test": case "test":
        return do_self_test(me);
    default:
        return notify_fail("驚異二針沒有這種針法。\n");
    }

    if( !objectp(target = needle_target(me, target)) )
        return notify_fail("這裡沒有可以施針的對象。\n");
    return do_amazing(me, kind, target);
}
