#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【文心雕龍】", ({ "The Literary Mind and Carving of Dragons", "the literary mind and carving of dragons", "the-literary-mind-and-carving-of-dragons", "literary", "mind", "carving", "dragons", "book", "【文心雕龍】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "細論文章的體裁、聲律與構思，循篇章脈絡探究如何遣詞、立意及雕琢文句。\n");
    set("required/skill", (["literate": 25, "archaic attainment": 10]));
    set("content", (["literate": 70, "archaic attainment": 70]));
    setup();
}
