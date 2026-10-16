// 善想禪要（absorption）。依使用者設計表（2026-10-16）。
//
// 1. 每升到 5 的倍數級，有機會增加慧根：沿用技能成長屬性的規則
//    （feature/char/skill.c 的 ATTR_GROWTH 表，absorption → wis）。
// 2. 每升到第 sk 級，獲得 sk × 30 點禪定修養（cultivation）與 sk × 30 點佛學修為（buddhology）。
//    一次升多級時每一級都給。只對玩家生效。
//    已經給到哪一級記在 skill_bonus/absorption，同一級一生只給一次。

inherit SKILL;

#define CULTIVATION_PER_LEVEL   30

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("absorption");
    setup();
}

void skill_improved(object me, string skill)
{
    me->apply_restored_skill_progression(skill);
}

void skill_advanced(object me, string skill)
{
    int done, now, lv, gain;

    if( !userp(me) ) return;

    now = me->query_skill(skill, 1);
    done = me->query("skill_bonus/absorption");
    if( now <= done ) return;

    me->set("skill_bonus/absorption", now);
    for(lv = done + 1; lv <= now; lv++) gain += lv * CULTIVATION_PER_LEVEL;
    if( gain > 0 ) {
        me->gain_score("cultivation", gain);
        // 同時獲得同量的佛學修為（每升到第 sk 級 sk × 30，使用者定案，2026-10-16）。
        me->gain_score("buddhology", gain);
    }
}
