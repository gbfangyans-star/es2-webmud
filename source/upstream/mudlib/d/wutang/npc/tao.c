// /d/wutang/npc/tao.c — 五堂鎮 NPC：小桃（依五堂鎮設計表）。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    seteuid(getuid());
    set_name("小桃", ({ "tao", "xiao tao" }));
    set_race("human");
    set_class("commoner");
    set_level(5);
    set("gender", "female");
    set("age", 10);
    set("long", @LONG
天真爛漫的小女孩，正盯著布莊李美麗的花布。
LONG
    );
    set_skill("unarmed", 10);
    set_skill("dodge", 10);
    set_skill("parry", 10);
    setup();
    set_stat_maximum("gin", 60);
    set_stat_effective("gin", 60);
    set_stat_current("gin", 60);
    set_stat_maximum("kee", 75);
    set_stat_effective("kee", 75);
    set_stat_current("kee", 75);
    set_stat_maximum("sen", 35);
    set_stat_effective("sen", 35);
    set_stat_current("sen", 35);
}
