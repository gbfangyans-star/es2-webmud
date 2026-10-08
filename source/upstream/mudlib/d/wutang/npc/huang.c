// /d/wutang/npc/huang.c — 五堂鎮 NPC：小黃（依五堂鎮設計表）。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    seteuid(getuid());
    set_name("小黃", ({ "shipman", "huang" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("age", 15);
    set("long", @LONG
一位年輕氣壯、精力旺盛的小伙子。
LONG
    );
    set_skill("unarmed", 2);
    set_skill("dodge", 2);
    set_skill("parry", 2);
    set_power("C");
    setup();
}
