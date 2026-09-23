inherit "/daemon/skill/taoism-spells";

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("taoism-freeze");
    setup();
}

string school() { return "freeze"; }