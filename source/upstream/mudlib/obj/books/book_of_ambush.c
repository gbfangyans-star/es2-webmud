// /obj/books/book_of_ambush.c — 【奇兵摘要】。依使用者設計表（2026-10-16）。

#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
    set_name("【奇兵摘要】", ({ "book of ambush", "ambush", "book", "【奇兵摘要】" }));
    set_weight(1000);
    set("unit", "本");
    set("value", 200);
    set("long", "一本【奇兵摘要】，摘錄歷代兵家出奇制勝的戰例，講述如何趁敵不備、攻其無防。\n");
    set("required/skill", (["literate": 30]));
    set("content", (["literate": 75, "backstab": 60]));
    setup();
}
