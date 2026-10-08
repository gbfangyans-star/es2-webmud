// /d/wutang/npc/jeweller.c — 五堂鎮 NPC：珍寶商人（依五堂鎮設計表）。

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
    set_name("珍寶商人", ({ "jeweller", "merchant" }));
    set_race("human");
    set_class("commoner");
    set_level(10);
    set("age", 40);
    set("long", @LONG
在天朝各處收集珍寶的商人，不僅身懷異寶還頗有歷練。你可以用 list 看他賣些什麼，用 buy 購買。
LONG
    );
    set_skill("unarmed", 20);
    set_skill("dodge", 20);
    set_skill("parry", 20);
    // merchandise 的數字是庫存份數，價錢是各物品自己的 value。
    set("merchandise", ([
        "/custom/armor/finger/han_jade_ring" : 5,
        "/custom/armor/finger/white_jade_ring" : 5,
        "/d/lee/obj/yellow_jade_ring" : 5,
    ]));
    set_power("C");
    setup();
}
