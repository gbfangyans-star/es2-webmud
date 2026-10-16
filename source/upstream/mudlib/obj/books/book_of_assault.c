// /obj/books/book_of_assault.c — 【奇兵精意】。依使用者設計表（2026-10-16）。

#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【奇兵精意】", ({ "book of assault", "assault", "book", "【奇兵精意】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "一本【奇兵精意】，深入剖析伏擊與突襲的要訣，書頁邊上還有前人留下的批註，筆跡凌厲。\n");
    set("required/skill", (["literate": 60, "backstab": 45]));
    set("content", (["literate": 120, "backstab": 140]));
    setup();
}
