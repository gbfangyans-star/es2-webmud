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
    // merchandise 的數字是庫存份數。【脈經注】使用者決定先不賣。
    set("merchandise", ([
        "/obj/books/studies_of_famous_mountains" : 5,             // 【名山文考】
        "/obj/books/the_literary_mind_and_carving_of_dragons" : 5, // 【文心雕龍】
    ]));
    set_power("C");
    setup();
    carry_object("/obj/cloth")->wear();
}
