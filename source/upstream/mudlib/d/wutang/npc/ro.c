// /d/wutang/npc/ro.c — 五堂鎮 NPC：老駱（依五堂鎮設計表）。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    seteuid(getuid());
    set_name("老駱", ({ "shipman", "ro", "ferryman ro" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("age", 55);
    set("long", @LONG
一位在此討生活多年的船夫。
LONG
    );
    set_skill("unarmed", 2);
    set_skill("dodge", 2);
    set_skill("parry", 2);
    set_power("C");
    setup();
}
