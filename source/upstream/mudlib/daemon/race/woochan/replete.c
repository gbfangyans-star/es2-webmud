/* CUSTOM A-H RACE COMMAND: woochan replete */
#include <ansi.h>
inherit F_CLEAN_UP;
private void create() { seteuid(getuid()); }
int main(object me, string arg) {
    int age, water_cost, water_now;
    if (me->query_race() != "woochan") return notify_fail("你不是無腸，無法使用 replete。\n");
    if (me->is_busy()) return notify_fail("你正忙著。\n");
    if (me->query_stat("sen") < 20) return notify_fail("你的神不足 20 點。\n");
    age = me->query("age");
    me->consume_stat("sen", 20);
    me->heal_stat("gin", age);
    me->heal_stat("kee", age);
    me->heal_stat("sen", age);
    water_cost = me->query_stat_maximum("water") / 3;
    water_now = me->query_stat("water");
    if (water_now > 0) me->consume_stat("water", water_cost > water_now ? water_now : water_cost);
    me->start_busy(1);
    message_vision(HIG "$N腹中空鳴一聲，將體內水氣轉化為滋養精氣神的力量。\n" NOR, me);
    return 1;
}
int help(object me) { write("指令格式：replete\n消耗神 20，恢復精／氣／神受損的格子各「年紀」點，不恢復當前值；另扣飲水最大值 1/3，飲水不足可照常使用並最低扣至 0。無冷卻，busy 1 tick。\n"); return 1; }
