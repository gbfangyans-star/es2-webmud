/* CUSTOM A-H RACE COMMAND: yenhold breathe */
#include <ansi.h>
inherit F_CLEAN_UP;
#define BREATHE_COOLDOWN 2   /* 1 tick = one 2-second heartbeat */
private void create() { seteuid(getuid()); }
int main(object me, string arg) {
    object *enemy, ob;
    int damage, until, hit;
    if (me->query_race() != "yenhold") return notify_fail("你不是厭火，無法使用 breathe。\n");
    if (me->query_stat("sen") < 10) return notify_fail("你的神不足 10 點。\n");
    until = me->query("custom_race/cooldown/breathe");
    if (until > time()) return notify_fail("breathe 尚在冷卻中。\n");
    enemy = me->query_enemy();
    if (!arrayp(enemy) || !sizeof(enemy)) return notify_fail("你目前沒有敵人。\n");
    // 原始種族資料：火焰傷害 = 厭火本身氣目前值的 1/10 + 膽識x2。
    damage = me->query_stat("kee") / 10 + me->query_attr("cor") * 2;
    // 裝備的火焰傷害力（apply/damage_vs_fire）直接加上去。
    damage += me->query_temp("apply/damage_vs_fire");
    message_vision(HIR "$N胸口猛然鼓起，張口朝四周敵人噴出灼熱烈焰！\n" NOR, me);
    foreach (ob in enemy) {
        if (!objectp(ob) || environment(ob) != environment(me)) continue;
        ob->consume_stat("kee", damage, me); hit++;
    }
    if (!hit) return notify_fail("附近沒有可被火焰擊中的敵人。\n");
    me->consume_stat("sen", 10);
    me->set("custom_race/cooldown/breathe", time() + BREATHE_COOLDOWN);
    if (userp(me)) me->save();
    return 1;
}
int help(object me) { write("指令格式：breathe\n攻擊同房所有敵人；對每個敵人造成 氣傷害 = 氣目前值/10 + 膽識x2 + 裝備的火焰傷害力，消耗神 10，冷卻 1 tick。\n"); return 1; }
