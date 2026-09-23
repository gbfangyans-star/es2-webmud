#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【咬文嚼字】", ({ "Simple Guide to Words", "simple guide to words", "simple-guide-to-words", "simple", "guide", "words", "book", "【咬文嚼字】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "由常見字詞入手，解說字形、讀音與詞義，並附短句供讀者練習辨字和理解文章。\n");
    set("required/skill", (["literate": 30]));
    set("content", (["literate": 80]));
    setup();
}
