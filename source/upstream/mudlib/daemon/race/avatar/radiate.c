/* CUSTOM A-H RACE COMMAND: avatar radiate */
#include <ansi.h>
inherit F_CLEAN_UP;
#define RADIATE_COOLDOWN 60

private void create() { seteuid(getuid()); }
int main(object me, string arg) {
    int until;
    if (me->query_race() != "avatar") return notify_fail("你不是人類族，無法使用 radiate。\n");
    until = me->query("custom_race/cooldown/radiate");
    if (until > time()) return notify_fail("radiate 尚在冷卻中。\n");
    me->supplement_stat("gin", me->query_stat_maximum("gin") * 25 / 100);
    me->supplement_stat("kee", me->query_stat_maximum("kee") * 25 / 100);
    me->supplement_stat("sen", me->query_stat_maximum("sen") * 25 / 100);
    me->set("custom_race/cooldown/radiate", time() + RADIATE_COOLDOWN);
    if (userp(me)) me->save();
    message_vision(HIW "$N身上泛起一陣柔和光芒，精氣神迅速回復。\n" NOR, me);
    return 1;
}
int help(object me) { write("指令格式：radiate\n恢復精、氣、神各自最大值的 25%，冷卻 1 分鐘。\n"); return 1; }
