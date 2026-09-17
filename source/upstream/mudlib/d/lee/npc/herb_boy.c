// /d/lee/npc/herb_boy.c
// NEW（李家村復原版新增角色，非原始 ES2 資料，由專案成員指定人設）
// 醫館專用，取代原本共用的 npc/child.c，其他房間的小孩不受影響。

#include <npc.h>
inherit F_VILLAGER;
void create()
{
    set_name("小藥童", ({ "boy", "apprentice", "herb boy" }));
    set_race("human"); set_class("commoner"); set_level(5);
    set_attr("int", 20);
    set_stat_maximum("gin", 50);
    set_stat_maximum("kee", 80);
    set_stat_maximum("sen", 100);
    set("age", 15);
    set("long", "一個在醫館裡跑進跑出的藥童，衣袖上沾著搗藥留下的藥漬，手裡還捧著幾株曬乾的藥草，看來是聶晟身邊打雜幫手的孩子。\n");
    setup();
}

// MODIFIED: F_VILLAGER 預設的 accept_fight() 一律拒絕（return 0），
// 這裡讓小藥童也能被玩家發起 fight。
int accept_fight(object ob)
{
    return 1;
}
