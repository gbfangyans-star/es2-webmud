// /obj/books/book_of_pulse_notes.c — 【脈經注】。依使用者設計表（2026-10-16）。

#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【脈經注】", ({ "book", "pulse", "notes", "【脈經注】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "一本講述人體穴道經脈運行之理的醫書。\n");
    set("required/skill", (["literate": 30]));
    set("content", (["kee anatomy": 20]));
    setup();
}
