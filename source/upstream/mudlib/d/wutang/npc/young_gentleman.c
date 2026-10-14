// /d/wutang/npc/young_gentleman.c — 五堂鎮 NPC：青年公子（依五堂鎮設計表）。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    seteuid(getuid());
    set_name("青年公子", ({ "young man", "young gentleman" }));
    set_race("human");
    set_class("commoner");
    set_level(10);
    set("age", 18);
    set("long", @LONG
一位衣著講究的青年公子，手搖摺扇，在布莊裡挑挑揀揀，看來是鎮上富
貴人家的少爺，正打算挑塊上好的綢緞做件新衣裳。
LONG
    );
    set_skill("unarmed", 20);
    set_skill("dodge", 20);
    set_skill("parry", 20);
    set_power("C");
    setup();
}
