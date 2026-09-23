inherit "/daemon/skill/taoism-spells";

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("taoism-storm");
    setup();
}

string school() { return "storm"; }