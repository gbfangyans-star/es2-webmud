// /obj/books/book_of_wordless_sutra.c — 【無字真經】。依使用者設計表（2026-10-16）。

#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【無字真經】", ({ "book of wordless sutra", "wordless", "sutra", "book", "【無字真經】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "一本【無字真經】，翻開來每一頁都是空白，只有禪定功夫極深的人，才能從一片空白之中悟出真意。\n");
    set("required/skill", (["absorption": 160]));
    set("content", (["absorption": 200]));
    setup();
}
