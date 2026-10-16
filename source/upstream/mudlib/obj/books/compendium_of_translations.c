#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【百家譯典】", ({ "book of morality", "morality", "book", "【百家譯典】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "一本從古時流傳下來的書﹐記載著許多寓言典故﹐深入淺出的講解為人處事的道理。\n");
    set("required/skill", (["literate": 75]));
    set("content", (["literate": 200]));
    setup();
}
