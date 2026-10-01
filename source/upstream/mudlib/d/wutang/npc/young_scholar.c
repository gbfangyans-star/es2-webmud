// /d/wutang/npc/young_scholar.c — 五堂鎮 NPC：青年書生（依五堂鎮設計表）。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    seteuid(getuid());
    set_name("青年書生", ({ "young scholar", "scholar" }));
    set_race("human");
    set_class("commoner");
    set_level(10);
    set("age", 25);
    set("long", @LONG
一個相貌斯文的青年書生正獨自一人在這裡沈思。
LONG
    );
    set_skill("unarmed", 20);
    set_skill("dodge", 20);
    set_skill("parry", 20);
    setup();
    set_stat_maximum("gin", 120);
    set_stat_effective("gin", 120);
    set_stat_current("gin", 120);
    set_stat_maximum("kee", 150);
    set_stat_effective("kee", 150);
    set_stat_current("kee", 150);
    set_stat_maximum("sen", 50);
    set_stat_effective("sen", 50);
    set_stat_current("sen", 50);
    carry_object("/custom/weapon/sword/jeweled_shortsword")->wield();
    carry_object("/d/wutang/obj/blue_cloth")->wear();
    carry_object("/obj/books/anthology_of_classical_prose");
}
