/* CUSTOM A-H RACE COMMAND: dingling hoof */
#include <ansi.h>
inherit F_CLEAN_UP;
private void create() { seteuid(getuid()); }
int main(object me, string arg) {
    object victim;
    int mine, theirs, ratio, roll, damage;
    if (me->query_race() != "dingling") return notify_fail("你不是釘靈，無法使用 hoof。\n");
    if (me->is_busy()) return notify_fail("你正忙著。\n");
    if (!arg || !objectp(victim = present(arg, environment(me))) || !victim->is_character() || victim == me)
        return notify_fail("你要踢誰？\n");
    if (!me->is_fighting(victim)) return notify_fail("你必須先與對方進入戰鬥。\n");
    mine = me->query_ability("move"); theirs = victim->query_ability("move"); if (theirs < 1) theirs = 1;
    ratio = (mine * 3 / 2) / theirs; roll = 1 + random(5);
    if (roll < ratio) {
        damage = me->query("age") + mine / 10;
        victim->consume_stat("HP", damage, me);
        victim->start_busy(2);
        message_vision(HIY "$N猛然揚蹄踢中$n，強勁衝力令$n一時站立不穩！\n" NOR, me, victim);
        return 1;
    }
    me->start_busy(2);
    message_vision("$N一蹄踢空，身形失衡。\n", me);
    return 1;
}
int help(object me) { write("指令格式：hoof <人物>\n成功造成「年紀 + 行動力/10」傷害並令目標 busy 2 tick；失敗自己 busy 2 tick。\n"); return 1; }
