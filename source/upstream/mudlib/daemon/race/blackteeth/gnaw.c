/* CUSTOM A-H RACE COMMAND: blackteeth gnaw */
#include <ansi.h>
inherit F_CLEAN_UP;
private void create() { seteuid(getuid()); }
int main(object me, string arg) {
    object victim;
    int damage, duration, age, mine, theirs, ratio, roll;
    mapping data;
    if (me->query_race() != "blackteeth") return notify_fail("你不是黑齒，無法使用 gnaw。\n");
    if (!arg || !objectp(victim = present(arg, environment(me))) || !victim->is_character() || victim == me)
        return notify_fail("你要咬誰？\n");
    if (environment(me)->query("no_fight") || victim->query("no_fight")) return notify_fail("這裡不能這麼做。\n");
    if (!me->is_fighting(victim)) return notify_fail("你必須先與對方進入戰鬥。\n");

    age = me->query("age");
    damage = me->query_stat("gin") / 100 + age / 10;
    victim->consume_stat("kee", damage, me);
    message_vision(HIR "$N猛然張口咬住$n，狠狠地撕咬了一口！\n" NOR, me, victim);

    // Poison only lands on top of a successful bite: roll 1~3, success if
    // the roll is below (own(gin+kee) x1.5 / opponent(gin+kee)) -- the same
    // "ratio of a combined stat, dice under it wins" shape as hide/hoof.
    mine = me->query_stat("gin") + me->query_stat("kee");
    theirs = victim->query_stat("gin") + victim->query_stat("kee"); if (theirs < 1) theirs = 1;
    ratio = (mine * 3 / 2) / theirs;
    roll = 1 + random(3);
    if (roll < ratio) {
        duration = age / 20; if (duration < 1) duration = 1;
        load_object("/custom/race/condition/blackteeth_gnaw");
        data = ([
            "duration":duration,
            "tick_interval":5,
            "ticks_until_next":5,
            "current_kee_loss":5 + age / 8,
            "max_kee_loss":age / 8
        ]);
        victim->set_condition("blackteeth_gnaw", data);
        message_vision(HIR "齒間的毒性隨傷口滲入了$n的體內！\n" NOR, me, victim);
    }
    return 1;
}
int help(object me) {
    write("指令格式：gnaw <人物>\n"
        "黑齒咬擊造成 (自身精/100 + 自身年紀/10) 點氣傷害。\n"
        "另外機率附加中毒：骰 1~3 < 自身(精+氣)x1.5 / 對手(精+氣) 則中毒。\n"
        "中毒後每 5 tick 發作一次，每次扣目標 (5+自身年紀/8) 點氣目前值，並使其氣上限降低 自身年紀/8，發作次數為自身年紀/20 次（所有除法取整數，毒性最少發作 1 次）。\n");
    return 1;
}
