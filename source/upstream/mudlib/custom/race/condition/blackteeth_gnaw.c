/* CUSTOM A-H RACE CONDITION: blackteeth gnaw poison */
#include <condition.h>
inherit CONDITION;

#define TICK_SECONDS 2

private void create() {
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("blackteeth_gnaw");
}

// The poison fires once per tick (one 2-second heartbeat). Conditions are
// only updated every 5~14 heartbeats, which is too coarse, so the ticks are
// driven by a call_out chain started from condition_apply(). The chain
// carries the data's serial so a replaced or removed poison stops its own
// chain. Keep this daemon loaded while chains may be pending.
int clean_up() { return 1; }

void poison_tick(object me, int serial) {
    mapping data;
    if (!objectp(me)) return;
    data = me->query_condition("blackteeth_gnaw");
    if (!mapp(data) || data["serial"] != serial) return;
    if (!living(me) || data["duration"] < 1) {
        me->delete_condition("blackteeth_gnaw"); return;
    }
    if (data["kee_loss"] > 0) me->consume_stat("kee", data["kee_loss"], me);
    tell_object(me, "黑齒咬傷的毒性在你體內發作！\n");
    // Mutate in place: set_condition() would unapply/apply and start a
    // second chain.
    data["duration"] -= 1;
    if (data["duration"] < 1) me->delete_condition("blackteeth_gnaw");
    else call_out("poison_tick", TICK_SECONDS, me, serial);
}

void condition_apply(object me, string cnd, mixed data) {
    if (!mapp(data)) return;
    call_out("poison_tick", TICK_SECONDS, me, data["serial"]);
}
void condition_unapply(object me, string cnd, mixed data) { }
void condition_update(object me, string cnd, mixed data) {
    if (!mapp(data) || data["duration"] < 1) me->delete_condition(cnd);
}
