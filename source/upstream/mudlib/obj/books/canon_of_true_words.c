#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【真言經】", ({ "Canon of True Words", "canon of true words", "canon-of-true-words", "canon", "true", "words", "book", "【真言經】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "記載古老真言及其音義，以艱深經文串聯五行變化，逐層揭示其中的陰陽法則。\n");
    set("required/skill", (["archaic attainment": 160, "mysticism": 145]));
    set("content", (["archaic attainment": 200, "mysticism": 200]));
    setup();
}
