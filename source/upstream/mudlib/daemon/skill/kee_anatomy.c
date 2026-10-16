// 經脈穴道之學（kee anatomy）。依使用者設計表（2026-10-16）。
//
// 每升到 5 的倍數級，精、氣、神的最大值各加 10。只對玩家生效。
// 已經給到哪一級記在 skill_bonus/kee anatomy，同一個門檻一生只給一次
// （放棄後重練、重複升到同一級都不會重複給）。提升時不顯示訊息。

inherit SKILL;

#define STEP    5
#define BONUS   10

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("kee anatomy");
    setup();
}

void skill_improved(object me, string skill)
{
    me->apply_restored_skill_progression(skill);
}

void skill_advanced(object me, string skill)
{
    int done, now, gain;

    if( !userp(me) ) return;

    now = me->query_skill(skill, 1) / STEP * STEP;
    done = me->query("skill_bonus/kee anatomy");
    if( now <= done ) return;

    me->set("skill_bonus/kee anatomy", now);
    gain = (now - done) / STEP * BONUS;
    foreach(string stat in ({ "gin", "kee", "sen" }))
        me->set_stat_maximum(stat, me->query_stat_maximum(stat) + gain);
}
