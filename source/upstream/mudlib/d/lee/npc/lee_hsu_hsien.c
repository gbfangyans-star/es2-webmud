// /d/lee/npc/lee_hsu_hsien.c
// NEW（李家村復原版新增角色，非原始 ES2 資料，由專案成員指定人設，取代原本未證實的私塾先生佔位角色）

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    set_name("李勖賢", ({ "lee hsu hsien", "hsu hsien", "lee", "hsu", "hsien" }));
    set_attr("int", 30);
    set_race("human");
    set_class("commoner");
    set_level(10);
    set("long", "李勖賢是村裡的文士，有秀才的頭銜，矮小的身裁給人很瘦弱的感覺，現在正\n指導學童唸著書。\n");
    setup();
}
