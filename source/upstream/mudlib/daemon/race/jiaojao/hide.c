/* CUSTOM A-H RACE COMMAND: jiaojao hide */
#include <ansi.h>
inherit F_CLEAN_UP;
private void create() { seteuid(getuid()); }
int main(object me, string arg) {
    object *enemy, ob;
    int mine, highest, ratio, roll;
    if (me->query_race() != "jiaojao") return notify_fail("你不是焦僥，無法使用 hide。\n");
    if (me->is_busy()) return notify_fail("你正忙著。\n");
    if (!me->is_fighting()) return notify_fail("你必須在戰鬥中才能藉機躲藏。\n");
    enemy = me->query_enemy(); highest = 1;
    foreach (ob in enemy) {
        int aw;
        if (!objectp(ob) || environment(ob) != environment(me)) continue;
        aw = ob->query_ability("awarness"); if (aw > highest) highest = aw;
    }
    mine = me->query_ability("awarness");
    ratio = (mine * 3 / 2) / highest;
    roll = 1 + random(5);
    if (roll < ratio) {
        me->remove_all_killer();
        me->set_temp("pending/hidden", mine * 3 / 2 + 1);
        message_vision(HIC "$N身形一晃脫離戰圈，轉眼便藏在原地陰影之中。\n" NOR, me);
        return 1;
    }
    me->start_busy(1);
    message_vision("$N試圖趁亂躲藏，卻被對手牢牢盯住。\n", me);
    return 1;
}
int help(object me) { write("指令格式：hide\n戰鬥中逃逸並原地躲藏；多人戰鬥以警覺性最高的敵人進行判定，失敗 busy 1 tick。\n"); return 1; }
