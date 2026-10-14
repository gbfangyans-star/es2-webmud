// /d/oldpine/npc/herbalist.c — 迷霧森林 NPC：採藥人（依老松林設計表）。

#include <npc.h>

inherit F_VILLAGER;


// 身上隨機帶一種草藥（龍涎草或野山蔘），每次 2～4 株。
void give_herb()
{
    object herb = new(({ "/obj/drug/dragon_saliva", "/obj/drug/wild_ginseng" })[random(2)]);

    herb->set_amount(2 + random(3));
    herb->move(this_object());
}

void create()
{
    seteuid(getuid());
    set_name("採藥人", ({ "herbalist" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("age", 22);
    set("long", @LONG
身材健碩的小伙子，經常在人煙罕至的地方收集草藥。
LONG
    );
    set_skill("unarmed", 2);
    set_skill("dodge", 2);
    set_skill("parry", 2);
    set_power("C");
    setup();
    give_herb();
}
