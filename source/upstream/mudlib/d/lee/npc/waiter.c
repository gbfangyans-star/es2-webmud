#include <npc.h>
inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("店小二", ({ "waiter", "lee waiter" }));
    set_race("human");
    set_class("commoner");
    set_level(2);
    set("age", 22);
    set("long", "李家村小旅店的店小二，動作俐落，忙著替往來客人端茶送飯。你可以用 list 看菜單，再用 buy 購買。\n");
    set("merchandise", ([
        "/obj/food/pork" : 30,
        "/obj/food/dumpling" : 50,
        "/obj/food/manto" : 50,
    ]));
    setup();
}

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}
