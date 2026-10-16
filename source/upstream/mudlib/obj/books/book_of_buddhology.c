// /obj/books/book_of_buddhology.c — 【般若波羅密多心經】。依使用者設計表（2026-10-16）。

#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【般若波羅密多心經】", ({ "book of buddhology", "buddhology", "book", "【般若波羅密多心經】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "一本【般若波羅密多心經】，經文簡短，卻字字闡述色空不二的般若智慧，是佛門弟子入門必讀的經典。\n");
    set("required/skill", (["literate": 10, "archaic attainment": 0]));
    set("required/class", "monk");
    set("content", (["literate": 60, "archaic attainment": 25, "absorption": 30]));
    setup();
}
