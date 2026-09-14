/* CUSTOM A-H RACE COMMAND: yenhold breathe */
#include <ansi.h>
inherit F_CLEAN_UP;
#define BREATHE_COOLDOWN 4
private void create() { seteuid(getuid()); }
int main(object me, string arg) {
    object *enemy, ob;
    int min_dam, max_dam, damage, until, hit;
    if (me->query_race() != "yenhold") return notify_fail("你不是厭火，無法使用 breathe。\n");
    if (me->query_stat("sen") < 10) return notify_fail("你的神不足 10 點。\n");
    until = me->query("custom_race/cooldown/breathe");
    if (until > time()) return notify_fail("breathe 尚在冷卻中。\n");
    enemy = me->query_enemy();
    if (!arrayp(enemy) || !sizeof(enemy)) return notify_fail("你目前沒有敵人。\n");
    min_dam = me->query_stat_maximum("kee") / 12;
    max_dam = me->query_stat_maximum("kee") / 10;
    if (max_dam < min_dam) max_dam = min_dam;
    message_vision(HIR "$N胸口猛然鼓起，張口朝四周敵人噴出灼熱烈焰！\n" NOR, me);
    foreach (ob in enemy) {
        if (!objectp(ob) || environment(ob) != environment(me)) continue;
        damage = me->query("age") + min_dam + random(max_dam - min_dam + 1);
        ob->consume_stat("HP", damage, me); hit++;
    }
    if (!hit) return notify_fail("附近沒有可被火焰擊中的敵人。\n");
    me->consume_stat("sen", 10);
    me->set("custom_race/cooldown/breathe", time() + BREATHE_COOLDOWN);
    if (userp(me)) me->save();
    return 1;
}
int help(object me) { write("指令格式：breathe\n攻擊同房所有敵人；傷害為年紀 + 氣最大值的 1/12～1/10，消耗神 10，冷卻 2 tick。\n"); return 1; }
