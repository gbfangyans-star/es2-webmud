/* CUSTOM A-H RACE CONDITION: headless glory/fury/axe dance buff */
#include <ansi.h>
#include <condition.h>
inherit CONDITION;

#define TICK_SECONDS 2

private void create() {
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("headless_dance");
}

// Durations count ticks (one 2-second heartbeat). Conditions are only
// updated every 5~14 heartbeats, so the countdown is a call_out chain
// started from condition_apply() and tied to the data's serial. Keep this
// daemon loaded while chains may be pending.
int clean_up() { return 1; }

private void apply_bonus(object me, mapping data, int sign) {
    switch (data["mode"]) {
    case "glory":
        me->add_temp("apply/damage", sign * data["damage_bonus"]);
        me->add_temp("apply/armor", sign * data["armor_bonus"]);
        break;
    case "fury":
        me->add_temp("apply/damage", sign * data["damage_bonus"]);
        me->add_temp("apply/intimidate", sign * data["intimidate_bonus"]);
        break;
    case "axe":
        me->add_temp("apply/axe", sign * data["axe_bonus"]);
        me->add_temp("apply/secondhand axe", sign * data["axe_bonus"]);
        me->add_temp("apply/twohanded axe", sign * data["axe_bonus"]);
        break;
    }
}

void dance_tick(object me, int serial) {
    mapping data;
    if (!objectp(me)) return;
    data = me->query_condition("headless_dance");
    if (!mapp(data) || data["serial"] != serial) return;
    // Mutate in place: set_condition() would unapply/apply and start a
    // second chain.
    data["duration"] -= 1;
    if (data["duration"] < 1) {
        me->delete_condition("headless_dance");
        tell_object(me, "你戰舞的效果漸漸消退了。\n");
        return;
    }
    call_out("dance_tick", TICK_SECONDS, me, serial);
}

void condition_apply(object me, string cnd, mixed data) {
    if (!mapp(data)) return;
    apply_bonus(me, data, 1);
    call_out("dance_tick", TICK_SECONDS, me, data["serial"]);
}

void condition_unapply(object me, string cnd, mixed data) {
    // `data` is unreliable here: delete_condition() (unlike set_condition()'s
    // replace path) calls this WITHOUT the data argument. In both call paths
    // the stored condition data hasn't been removed yet at this point, so
    // fetch it directly instead of trusting the parameter.
    data = me->query_condition(cnd);
    if (!mapp(data)) return;
    apply_bonus(me, data, -1);
}

void condition_update(object me, string cnd, mixed data) {
    if (!living(me) || !mapp(data) || data["duration"] < 1) me->delete_condition(cnd);
}
