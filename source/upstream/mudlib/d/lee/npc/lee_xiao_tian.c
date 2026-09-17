#include <npc.h>
inherit F_VILLAGER;

void create()
{
    set_name("李嘯天", ({ "lee xiao tian", "li xiao tian", "manager lee", "lee", "li", "xiao", "tian" }));
    set_race("human");
    set_class("commoner");
    set_level(20);
    set_attr("cor", 25);
    set_stat_maximum("gin", 180);
    set_stat_maximum("kee", 180);
    set_stat_maximum("sen", 100);
    set_skill("parry", 50);
    set_skill("dodge", 50);
    set_skill("unarmed", 50);
    set_skill("blade", 30);
    set("age", 40);
    set("long", "李員外家的二總管為人精明，年少時好舞刀弄槍，被派任當鋪掌櫃之後，諸事都處理得緊緊有條。\n");
    set("chat_chance", 1);
    set("chat_msg", ({ "李嘯天低頭翻著帳簿，偶爾撥動算盤珠。\n" }));
    setup();
    carry_object("/d/lee/obj/yellow_jade_ring")->wear();
    carry_object("/d/lee/obj/willow_blade")->wield();
}
