#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name(HIW "【咬文嚼字】" NOR, ({ "advanced book of words", "advanced", "words", "book", "【咬文嚼字】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "一本【咬文嚼字】﹐以探討文字的來源和聯係為主的書籍。\n");
    set("required/skill", (["literate": 120, "archaic attainment": 110]));
    set("content", (["literate": 170, "archaic attainment": 200]));
    setup();
}
