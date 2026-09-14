#include <npc.h>
inherit F_VILLAGER;
void create()
{
    set_name("婦人", ({ "woman", "lee woman" }));
    set_race("human"); set_class("commoner"); set_level(2);
    set("age", 34);
    set("long", "一名住在李家村的婦人，手裡忙著家務，遇上熟人便停下來聊幾句村裡近況。\n");
    setup();
}
