// /d/qiaoyin/npc/girl.c — 喬陰縣 NPC：小女孩（依使用者設計表，2026-10-16）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("小女孩", ({ "girl" }));
    set_race("human");
    set_class("fighter");
    set_level(5);
    set("gender", "female");
    set("age", 11);
    set("long", @LONG
稚氣未脫的小女孩，扛著一把長劍站在路邊，對著來往的過客大聲吆喝。
LONG
    );
    set_power("B");
    setup();
    carry_object("/obj/area/obj/longsword")->wield();
}
