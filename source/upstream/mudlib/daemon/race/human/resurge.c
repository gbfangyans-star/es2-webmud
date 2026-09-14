/* CUSTOM A-H RACE COMMAND: human resurge */
#include <ansi.h>
inherit F_CLEAN_UP;
#define RESURGE_COOLDOWN 360

private void create() { seteuid(getuid()); }

int main(object me, string arg) {
    int hp, hpmax, kee, keemax, until;
    if (me->query_race() != "human") return notify_fail("你不是人類，無法使用 resurge。\n");
    hp = me->query_stat("HP"); hpmax = me->query_stat_maximum("HP");
    kee = me->query_stat("kee"); keemax = me->query_stat_maximum("kee");
    if (hpmax < 1 || keemax < 1) return notify_fail("你目前無法運行復甦之力。\n");
    if (hp * 4 > hpmax && kee * 4 > keemax)
        return notify_fail("只有形體或氣降到最大值四分之一以下時才能使用 resurge。\n");
    until = me->query("custom_race/cooldown/resurge");
    if (until > time()) return notify_fail("你的復甦之力尚未恢復。\n");

    me->supplement_stat("HP", hpmax / 2);
    me->supplement_stat("kee", keemax * 3 / 4);
    me->set("custom_race/cooldown/resurge", time() + RESURGE_COOLDOWN);
    if (userp(me)) me->save();
    message_vision(HIG "$N深吸一口氣，體內殘存的生命力驟然重新湧起。\n" NOR, me);
    return 1;
}

int help(object me) {
    write("指令格式：resurge\n形體或氣低於或等於最大值 25% 時可用；恢復形體最大值 50% 與氣最大值 75%，冷卻為 ES2 四分之一天。\n");
    return 1;
}
