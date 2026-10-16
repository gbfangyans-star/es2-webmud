// /d/qiaoyin/npc/keeper.c — 喬陰縣 NPC：同仁藥鋪掌櫃（依使用者設計表，2026-10-16）。

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
    set_name("掌櫃", ({ "keeper" }));
    set("title", "同仁藥鋪");
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("gender", "male");
    set("age", 50);
    set("long", @LONG
同仁藥鋪的掌櫃，一身半舊的長衫，袖口沾著些藥粉，對各種常用藥材與丹藥都十分熟悉。
LONG
    );
    set("merchandise", ([
        "/obj/medication/black_pill" : 30,                // 烏心丹
        "/obj/medication/boar_berry" : 20,                // 山豬果
        "/obj/medication/dragon_saliva" : 20,             // 龍涎草
        "/obj/medication/alchemist/aquapill" : 20,        // 金液丹
        "/d/lee/obj/bronze_furnace" : 20,                 // 青銅丹爐
        "/d/lee/obj/bronze_reactor" : 50,                 // 青銅丹鼎
        "/d/lee/obj/firewood" : 3000,                     // 松材
    ]));
    set_power("C");
    setup();
    carry_object("/obj/cloth")->wear();
}
