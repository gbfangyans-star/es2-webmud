/* CUSTOM A-H RACE CONDITION: blackteeth gnaw poison */
#include <condition.h>
inherit CONDITION;

private void create() {
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("blackteeth_gnaw");
}
void condition_apply(object me, string cnd, mixed data) { }
void condition_unapply(object me, string cnd, mixed data) { }
void condition_update(object me, string cnd, mixed data) {
    int current_loss, max_loss, interval;
    if (!living(me) || !mapp(data) || data["duration"] < 1) {
        me->delete_condition(cnd); return;
    }

    // This condition daemon's own update() is driven once per heart_beat
    // (1 tick), but the poison itself should only actually fire every 5
    // ticks -- so most calls just count down "ticks_until_next" and do
    // nothing visible yet.
    interval = data["tick_interval"]; if (interval < 1) interval = 1;
    data["ticks_until_next"] -= 1;
    if (data["ticks_until_next"] > 0) {
        me->set_condition(cnd, data);
        return;
    }
    data["ticks_until_next"] = interval;

    current_loss = data["current_kee_loss"];
    max_loss = data["max_kee_loss"];
    if (current_loss > 0) me->consume_stat("kee", current_loss, me);
    if (max_loss > 0) me->damage_stat("kee", max_loss, me);
    tell_object(me, "黑齒咬傷的毒性在你體內發作！\n");
    data["duration"] -= 1;
    if (data["duration"] < 1) me->delete_condition(cnd);
    else me->set_condition(cnd, data);
}
