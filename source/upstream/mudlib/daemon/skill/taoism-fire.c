inherit "/daemon/skill/taoism-spells";

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("taoism-fire");
    setup();
}

string school() { return "fire"; }