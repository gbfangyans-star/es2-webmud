#include <npc.h>
inherit F_VILLAGER;
void create()
{
    set_name("農夫", ({ "farmer", "lee farmer" }));
    set_race("human"); set_class("commoner"); set_level(4);
    set("age", 38);
    set("long", "一名常年在田裡工作的農夫，皮膚曬得黝黑，手掌粗糙，對田裡作物看得很緊。\n");
    setup();
}
