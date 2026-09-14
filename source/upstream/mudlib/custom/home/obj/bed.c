/* CUSTOM HOME SYSTEM - bedroom bed/rest mechanic.
 * User-approved WebMUD extension. Not canonical ES2 content.
 */
#include <ansi.h>

inherit ITEM;

object resting_player;

void create() {
    set_name(HIW "床" NOR, ({ "bed", "床", "木床" }));
    set_weight(1000000);
    set("unit", "張");
    setup();
}

string long(int raw) {
    return "一張鋪著乾淨被褥的木床，床架厚實，躺上去休息可以慢慢恢復精神與體力。\n"
           HIG "上床休息：rest bed 或 上床；離開床鋪：leave bed 或 下床。\n"
           "休息期間每一分鐘恢復精、氣、神各最大值的 10%。\n" NOR;
}

void init() {
    add_action("do_rest", "rest");
    add_action("do_rest", "上床");
    add_action("do_leave", "leave");
    add_action("do_leave", "下床");
}

void stop_rest(object me, string msg) {
    if (!me) return;
    me->delete("custom_home/bed_resting");
    if (resting_player == me) resting_player = 0;
    if (msg) tell_object(me, msg);
}

void rest_tick(object me) {
    string *stats;
    int i, maxv, cur, eff, gain, cap, changed;

    if (!me || !resting_player || resting_player != me ||
        environment(me) != environment(this_object()) ||
        !(int)me->query("custom_home/bed_resting")) {
        if (me) me->delete("custom_home/bed_resting");
        if (resting_player == me) resting_player = 0;
        return;
    }
    if (me->is_fighting()) {
        stop_rest(me, HIR "你受到戰鬥干擾，無法繼續躺床休息。\n" NOR);
        return;
    }

    stats = ({ "gin", "kee", "sen" });
    changed = 0;
    for (i = 0; i < sizeof(stats); i++) {
        maxv = (int)me->query_stat_maximum(stats[i]);
        cur = (int)me->query_stat_current(stats[i]);
        eff = (int)me->query_stat_effective(stats[i]);
        if (maxv < 1) continue;
        gain = maxv / 10;
        if (gain < 1) gain = 1;
        cap = eff > 0 && eff < maxv ? eff : maxv;
        if (cur < cap) {
            cur += gain;
            if (cur > cap) cur = cap;
            me->set_stat_current(stats[i], cur);
            changed = 1;
        }
    }

    if (changed)
        tell_object(me, HIG "你在床上安穩休息了一分鐘，精、氣、神各恢復了最大值的 10%。\n" NOR);
    else
        tell_object(me, HIC "你在床上安穩休息了一分鐘，精、氣、神目前已無需恢復。\n" NOR);
    call_out("rest_tick", 60, me);
}

int do_rest(string arg) {
    object me;
    me = this_player();
    if (query_verb() == "rest" && arg != "bed" && arg != "床")
        return notify_fail("你要在哪裡休息？\n");
    if (resting_player && resting_player != me)
        return notify_fail("床上已經有人了。\n");
    if (me->is_fighting())
        return notify_fail("戰鬥中不能上床休息。\n");
    if ((int)me->query("custom_home/bed_resting"))
        return notify_fail("你已經躺在床上休息了。\n");

    resting_player = me;
    me->set("custom_home/bed_resting", 1);
    tell_object(me, HIW "你躺上床，拉好被褥開始休息。每一分鐘會恢復 10% 的精、氣、神。\n" NOR);
    call_out("rest_tick", 60, me);
    return 1;
}

int do_leave(string arg) {
    object me;
    me = this_player();
    if (query_verb() == "leave" && arg != "bed" && arg != "床") return 0;
    if (!(int)me->query("custom_home/bed_resting"))
        return notify_fail("你現在沒有躺在床上。\n");
    stop_rest(me, HIW "你掀開被褥，從床上起身。\n" NOR);
    return 1;
}

int move(mixed dest) {
    if (objectp(dest) && dest->is_character()) return 0;
    return ::move(dest);
}
