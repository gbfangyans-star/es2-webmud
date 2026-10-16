// /d/qiaoyin/npc/oldman.c — 喬陰縣 NPC：老人（名山書肆）（依使用者設計表，2026-10-16）。

#include <npc.h>
inherit F_VILLAGER;
inherit F_VENDOR;

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}

void create()
{
    seteuid(getuid());
    set_name("老人", ({ "oldman", "old man" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("gender", "male");
    set("age", 68);
    set("long", @LONG
慢條斯理的老人家，賣些啟蒙書餬口維生。
LONG
    );
    // merchandise 的數字是庫存份數（使用者指定各 10 本，2026-10-16）。
    set("merchandise", ([
        "/obj/books/book_of_pulse_notes" : 10,                     // 【脈經注】
        "/obj/books/studies_of_famous_mountains" : 10,             // 【名山文考】
        "/obj/books/book_of_ambush" : 10,                          // 【奇兵摘要】
        "/obj/books/the_five_numbers" : 10,                        // 【五數】
        "/obj/books/the_literary_mind_and_carving_of_dragons" : 10, // 【文心雕龍】
        "/obj/books/book_of_buddhology" : 10,                      // 【般若波羅密多心經】
        "/obj/books/book_of_life" : 10,                            // 【無量壽經】
    ]));

    set_power("C");
    setup();
    carry_object("/obj/cloth")->wear();
}
