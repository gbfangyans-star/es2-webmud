// /d/lee/npc/nee_cheng.c
// NEW（李家村復原版新增角色，非原始 ES2 資料，由專案成員指定人設）

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    set_name("聶晟", ({ "nee cheng", "nee", "cheng" }));
    set_attr("spi", 30);
    set_attr("wis", 25);
    set_attr("int", 30);
    set_attr("cps", 28);
    set_attr("cor", 22);
    set_attr("str", 20);
    set_race("human");
    set_level(30);
    set_class("commoner");
    set_stat_maximum("gin", 200);
    set_stat_maximum("kee", 250);
    set_stat_maximum("sen", 300);
    set_skill("whip", 50);
    set_skill("parry", 40);
    set_skill("dodge", 40);
    set_skill("unarmed", 50);
    set("age", 40);
    set("long", @LONG
聶晟是李家村裡惟一不姓李的住民。十多年前，村裡許多的居民曾經得了一種怪病，聶晟
恰巧路過，治好了村民，於是李員外請他留下，成為村裡的大夫。
聶晟身形削瘦，做文人打扮，表情冷漠，似乎不太容易親近。
LONG
    );
    setup();
    carry_object("/d/snow/npc/obj/white_dress")->wear();
    carry_object("/d/lee/obj/crystal_ring")->wear();
    carry_object("/obj/area/obj/leather_whip")->wield();
}
