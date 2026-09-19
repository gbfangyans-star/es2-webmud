// recruit_stone.c -- 徵兵石, an immovable prop at 魯熙年's post that lets a
// qualifying commoner "enlist" to become a soldier.
#include <ansi.h>

inherit ITEM;

void create()
{
    set_name("徵兵石", ({"recruit stone", "recruitstone", "recruit", "stone"}));
    set("no_get", "徵兵石深植地下，任你怎麼使力也搬不動它。\n");
    set("long", "振武軍營徵兵處，可在此登記 (enlist) 成為軍人。\n");
    set_weight(999999);
    setup();
}

void init()
{
    add_action("do_enlist", "enlist");
}

int do_enlist(string arg)
{
    object me, who;

    me = this_player();
    if( !me || environment(me) != environment(this_object()) ) return 0;

    if( me->query_class() != "commoner" )
        return notify_fail("你已經有自己的身分了，振武軍營不收你這樣的人。\n");

    if( me->query("gender") != "male" )
        return notify_fail("振武軍營目前只招募男丁入伍。\n");

    me->set_class("soldier");
    me->set_skill("berserk", 1);
    me->set_learn("berserk", 1);
    me->set_skill("powerblow", 1);
    me->set_learn("powerblow", 1);
    me->set_skill("heavy_parry", 1);
    me->set_learn("heavy_parry", 1);

    // The rest of the welcome (魯熙年's dialogue, then the final
    // confirmation) plays out over several ticks -- see
    // lu_xinien.c:welcome_recruit().
    if( objectp(who = present("xinien", environment(this_object()))) )
        who->welcome_recruit(me);

    return 1;
}
