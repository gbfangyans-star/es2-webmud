// /d/qiaoyin/npc/crone.c — 喬陰縣 NPC：老乞婆（依使用者設計表，2026-10-16）。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    seteuid(getuid());
    set_name("老乞婆", ({ "crone" }));
    set_race("human");
    set_class("thief");
    set_level(3);
    set("gender", "female");
    set("age", 70);
    set("long", @LONG
一位老態龍鍾的婆婆，正蜷縮著身子窩在一旁，但你不知為何總覺得她的注意力全在你身上。
LONG
    );
    set_power("C");
    setup();
    carry_object("/obj/cloth")->wear();
}
