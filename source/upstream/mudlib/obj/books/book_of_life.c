// /obj/books/book_of_life.c — 【無量壽經】。依使用者設計表（2026-10-16）。

#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【無量壽經】", ({ "book of life", "life", "book", "【無量壽經】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "一本【無量壽經】，記載無量壽佛發下的四十八大願，以及西方淨土莊嚴殊勝的景象。\n");
    set("required/skill", (["literate": 20, "archaic attainment": 10, "absorption": 25]));
    set("content", (["literate": 90, "archaic attainment": 80, "absorption": 60]));
    setup();
}
