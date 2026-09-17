#include <npc.h>
inherit F_VILLAGER;
void create()
{
    set_name("農夫", ({ "farmer", "lee farmer" }));
    set_race("human"); set_class("commoner"); set_level(8);
    set_attr("cor", 18);
    set_stat_maximum("gin", 90);
    set_stat_maximum("kee", 75);
    set_stat_maximum("sen", 40);
    set("age", 25);
    set("long", "一名常年在田裡工作的農夫，皮膚曬得黝黑，手掌粗糙，對田裡作物看得很緊。\n");
    setup();
}
