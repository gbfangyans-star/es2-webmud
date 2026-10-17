inherit SKILL;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("archaic attainment");
    setup();
}

void skill_improved(object me, string skill)
{
    me->apply_restored_skill_progression(skill);
}

/* 文學造詣（score: literature mastery）：古文造詣每升到第 n 級給 n×30，
 * 以「累計應得 = 15 × 等級 × (等級 + 1)」補足差額，練過的等級也會一併補上。 */
void skill_advanced(object me, string skill)
{
    int lv, target, cur;

    if( !userp(me) ) return;
    lv = me->query_skill("archaic attainment", 1);
    target = 15 * lv * (lv + 1);
    cur = me->query_score("literature mastery");
    if( target > cur ) me->gain_score("literature mastery", target - cur);
}