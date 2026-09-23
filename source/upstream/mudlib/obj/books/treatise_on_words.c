#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name(HIW "【咬文嚼字】" NOR, ({ "Treatise on Words", "treatise on words", "treatise-on-words", "treatise", "on", "words", "book", "【咬文嚼字】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "深究古字訓詁、通假與詞義流變，參照不同典籍辨析一字在各篇中的細微差異。\n");
    set("required/skill", (["literate": 120, "archaic attainment": 110]));
    set("content", (["literate": 170, "archaic attainment": 200]));
    setup();
}
