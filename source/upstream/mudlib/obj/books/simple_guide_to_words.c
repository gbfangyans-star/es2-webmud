#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【咬文嚼字】", ({ "book of words", "words", "book", "【咬文嚼字】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "一本【咬文嚼字】﹐以探討文字的來源和聯係為主的書籍。你手中的這一本是簡化過的﹐所以應該不難理解。\n");
    set("required/skill", (["literate": 30]));
    set("content", (["literate": 80]));
    setup();
}
