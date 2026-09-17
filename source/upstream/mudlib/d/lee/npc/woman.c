#include <npc.h>
inherit F_VILLAGER;
void create()
{
    set_name("婦人", ({ "woman", "lee woman" }));
    set_race("human"); set_class("commoner"); set_level(8);
    set_attr("cor", 18);
    set_stat_maximum("gin", 80);
    set_stat_maximum("kee", 60);
    set_stat_maximum("sen", 40);
    set("age", 25);
    set("long", "一名住在李家村的婦人，手裡忙著家務，遇上熟人便停下來聊幾句村裡近況。\n");
    setup();
}
