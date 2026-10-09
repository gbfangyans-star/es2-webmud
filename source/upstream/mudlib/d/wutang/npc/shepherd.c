// /d/wutang/npc/shepherd.c — 五堂鎮 NPC：牧羊人（依五堂鎮設計表）。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    seteuid(getuid());
    set_name("牧羊人", ({ "sheep man", "shepherd" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("age", 15);
    set("long", @LONG
盯著羊群，時而發呆放空。
LONG
    );
    set_skill("unarmed", 2);
    set_skill("dodge", 2);
    set_skill("parry", 2);
    set_power("C");
    setup();
}
