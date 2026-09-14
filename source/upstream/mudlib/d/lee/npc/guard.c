#include <npc.h>
inherit F_VILLAGER;
void create()
{
    set_name("守衛", ({ "guard", "lee guard" }));
    set_race("human"); set_class("fighter"); set_level(8);
    set("age", 28);
    set("long", "一名負責巡看李家村出入口的守衛，穿著便於行動的短裝，目光不時掃過來往行人。\n");
    setup();
}
