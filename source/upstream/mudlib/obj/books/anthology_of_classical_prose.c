#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【古文觀止】", ({ "Anthology of Classical Prose", "anthology of classical prose", "anthology-of-classical-prose", "anthology", "classical", "prose", "book", "【古文觀止】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "選錄歷代古文名篇，旁註典故與章法，使讀者能從字句之間體會古人的議論與情思。\n");
    set("required/skill", (["literate": 15]));
    set("required/class", "scholar");
    set("content", (["literate": 50, "archaic attainment": 20]));
    setup();
}
