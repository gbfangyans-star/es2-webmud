#include <npc.h>
inherit F_VILLAGER;
void create()
{
    set_name("小孩", ({ "child", "lee child" }));
    set_race("human"); set_class("commoner"); set_level(1);
    set("age", 10);
    set("long", "一個在村裡跑來跑去的小孩，衣角沾著灰土，像是剛從廣場玩回來。\n");
    setup();
}
