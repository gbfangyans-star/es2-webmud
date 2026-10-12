/*---
description: 重擊術（powerblow）。拿武器打中時有機會發動，傷害取武器最大值，
             判定見 feature/equip.c 的 inflict_damage()。
             這裡處理升級獎勵（使用者定案，2026-10-12）。
---*/
#include <ansi.h>
inherit SKILL;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("powerblow");
    setup();
}

/* 升級獎勵（每一級只給一次，powerblow/growth_level 記錄已給到第幾級）：
 *   100 級：精氣上限各 +20
 *   101 級起每級：精氣上限各 +2 */
private int level_stat(int lv)
{
    if( lv == 100 ) return 20;
    if( lv > 100 ) return 2;
    return 0;
}

void skill_advanced(object me, string skill)
{
    int lv, done, stat;

    if( !userp(me) ) return;
    lv = me->query_skill("powerblow", 1);
    /* 這套獎勵上線前就練過的等級不補發：第一次記錄時從這一級開始。 */
    if( !(done = me->query("powerblow/growth_level")) ) done = lv - 1;
    if( done >= lv ) return;
    me->set("powerblow/growth_level", lv);
    for(done++; done <= lv; done++) {
        if( !(stat = level_stat(done)) ) continue;
        me->advance_stat("gin", stat);
        me->advance_stat("kee", stat);
        /* 只有 100 級顯示訊息，之後每級的成長不提示。 */
        if( done == 100 )
            tell_object(me, HIY "千錘百鍊的重擊讓你的體魄更加強健﹐精、氣更加充沛了。\n" NOR);
    }
}
