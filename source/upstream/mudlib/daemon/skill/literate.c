inherit SKILL;

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("literate");
    setup();
}

void skill_improved(object me, string skill)
{
    me->apply_restored_skill_progression(skill);
}

void skill_advanced(object me, string skill)
{
}