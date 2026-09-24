/* CUSTOM A-H RACE CONDITION: headless war/glory dance buff */
#include <condition.h>
inherit CONDITION;

private void create() {
    seteuid(getuid());
    DAEMON_D->register_condition_daemon("headless_dance");
}

private void apply_bonus(object me, mapping data, int sign) {
    string mode = data["mode"];
    if (mode == "war") {
        me->add_temp("apply/damage", sign * data["damage_bonus"]);
        me->add_temp("apply/intimidate", sign * data["intimidate_bonus"]);
    } else if (mode == "glory") {
        me->add_temp("apply/defense", sign * data["defense_bonus"]);
        me->add_temp("apply/wittiness", sign * data["wittiness_bonus"]);
        me->add_temp("apply/armor_vs_fire", sign * data["element_bonus"]);
        me->add_temp("apply/armor_vs_ice", sign * data["element_bonus"]);
        me->add_temp("apply/armor_vs_wind", sign * data["element_bonus"]);
        me->add_temp("apply/armor_vs_lightning", sign * data["element_bonus"]);
    }
}

void condition_apply(object me, string cnd, mixed data) {
    if (!mapp(data)) return;
    apply_bonus(me, data, 1);
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
    if (!living(me) || !mapp(data)) { me->delete_condition(cnd); return; }
    data["duration"] -= 1;
    if (data["duration"] < 1) { me->delete_condition(cnd); return; }
    me->set_condition(cnd, data);
}
