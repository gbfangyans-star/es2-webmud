#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【十三靈頌】", ({ "book of myth", "myth", "book", "【十三靈頌】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "一本【十三靈頌】，是張天立遊覽天靈山時有感，歌頌寒於十三靈的長詩。此詩細膩動人，行文如歌如夢，倍受天朝文人推崇。\n");
    set("required/skill", (["literate": 60, "archaic attainment": 40]));
    set("content", (["literate": 100, "archaic attainment": 100]));
    setup();
}
