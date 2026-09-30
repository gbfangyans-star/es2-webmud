/* CUSTOM ARMOR CONDITION: 雨神祝福 (rain_blessing)
 *
 * 封印冰環（custom/armor/finger/freeze_ring.c）的 clutch：緊握戒指祝禱，
 * 咒文能力（apply/spell）增加 慧根 + random(咒術 / 20)，持續 慧根 個 tick
 * （1 tick = 一次心跳 2 秒）。冷卻 60 tick，從祝禱那一刻起算。
 *
 * 加成記在 condition 裡，重新登入時由 condition_apply() 補回；時間到由
 * call_out 結束，心跳的 condition_update() 作為備援。
 */
#include <condition.h>

inherit CONDITION;

#define TICK_SECONDS     2
#define COOLDOWN_TICKS   60
#define CD_PROP          "rain_blessing_cd"

// 冷卻時間寫在玩家資料裡，需要 euid 才能通過玩家資料保護。
void create() { seteuid(getuid()); }

// 結束靠 call_out，保持載入。
int clean_up() { return 1; }

void expire(object me, int serial);

void clutch(object me)
{
    int wis, amount;

    if( mapp(me->query_condition("rain_blessing")) ) {
        tell_object(me, "雨神的祝福依然庇蔭著你。\n");
        return;
    }
    if( me->query(CD_PROP) > time() ) {
        tell_object(me, "你持續喃喃祝禱，但似乎沒有任何感應。\n");
        return;
    }

    wis = me->query_attr("wis");
    amount = wis + random(me->query_skill("spells") / 20);
    me->set(CD_PROP, time() + COOLDOWN_TICKS * TICK_SECONDS);
    tell_object(me, "你受到雨神祝福，感覺體內靈力暴增。\n");
    me->set_condition("rain_blessing", ([
        "amount":   amount,
        "until":    time() + wis * TICK_SECONDS,
        "serial":   time() * 1000 + random(1000),
    ]));
}

private void finish(object me)
{
    tell_object(me, "你心神一怔，似乎有些神力消散了。\n");
    me->delete_condition("rain_blessing");
}

void expire(object me, int serial)
{
    mapping data;

    if( !objectp(me) ) return;
    data = me->query_condition("rain_blessing");
    if( !mapp(data) || data["serial"] != serial ) return;
    finish(me);
}

// 祝禱或重新登入時加上咒文能力，並排定結束時間。
void condition_apply(object me, string cnd, mixed data)
{
    int left;

    if( !mapp(data) ) return;
    me->add_temp("apply/spell", data["amount"]);
    left = data["until"] - time();
    call_out("expire", left > 0 ? left : 1, me, data["serial"]);
}

// delete_condition() 呼叫時不帶 data，從身上的 condition 取。
varargs void condition_unapply(object me, string cnd, mixed data)
{
    if( !mapp(data) ) data = me->query_condition(cnd);
    if( mapp(data) ) me->add_temp("apply/spell", -data["amount"]);
}

void condition_update(object me, string cnd, mixed data)
{
    if( !mapp(data) ) me->delete_condition(cnd);
    else if( data["until"] <= time() ) finish(me);
}
