#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【六陰八卦譜】", ({ "Manual of Six Yin and Eight Trigrams", "manual of six yin and eight trigrams", "manual-of-six-yin-and-eight-trigrams", "manual", "six", "yin", "eight", "trigrams", "book", "【六陰八卦譜】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "將六陰之理配合八卦卦象，列出各種組合與推演次序，說明其中陰陽消長的規律。\n");
    set("required/skill", (["literate": 95, "archaic attainment": 75]));
    set("content", (["literate": 125, "archaic attainment": 125, "mysticism": 90]));
    setup();
}
