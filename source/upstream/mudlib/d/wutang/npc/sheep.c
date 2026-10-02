// /d/wutang/npc/sheep.c — 五堂鎮 NPC：綿羊（依五堂鎮設計表）。

#include <npc.h>

void create()
{
    seteuid(getuid());
    set_name("綿羊", ({ "sheep" }));
    set_race("beast");
    set_class("commoner");
    set_level(1);
    set("age", 3);
    set("long", @LONG
整天只會咩咩跟吃草，頗為愜意。
LONG
    );
    setup();
}
