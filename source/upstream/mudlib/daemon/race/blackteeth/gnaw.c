/* CUSTOM A-H RACE COMMAND: blackteeth gnaw */
#include <ansi.h>
inherit F_CLEAN_UP;
private void create() { seteuid(getuid()); }
int main(object me, string arg) {
    object victim;
    int damage, duration, age, target_age;
    mapping data;
    if (me->query_race() != "blackteeth") return notify_fail("你不是黑齒，無法使用 gnaw。\n");
    if (!arg || !objectp(victim = present(arg, environment(me))) || !victim->is_character() || victim == me)
        return notify_fail("你要咬誰？\n");
    if (environment(me)->query("no_fight") || victim->query("no_fight")) return notify_fail("這裡不能這麼做。\n");
    if (!me->is_fighting(victim)) return notify_fail("你必須先與對方進入戰鬥。\n");

    age = me->query("age"); target_age = victim->query("age");
    damage = me->query_stat("gin") / 100 + age / 10;
    duration = age / 20; if (duration < 1) duration = 1;
    victim->consume_stat("HP", damage, me);
    load_object("/custom/race/condition/blackteeth_gnaw");
    data = ([
        "duration":duration,
        "current_kee_loss":target_age / 2,
        "max_kee_loss":target_age / 4
    ]);
    victim->set_condition("blackteeth_gnaw", data);
    message_vision(HIR "$N猛然張口咬住$n，齒間毒性隨傷口滲入體內！\n" NOR, me, victim);
    return 1;
}
int help(object me) { write("指令格式：gnaw <人物>\n黑齒咬擊並附加毒性。所有除法取整數，毒性最少發作 1 次。\n"); return 1; }
