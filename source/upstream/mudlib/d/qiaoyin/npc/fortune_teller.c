// /d/qiaoyin/npc/fortune_teller.c — 喬陰縣 NPC：算命先生（依使用者設計表，2026-10-16）。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    seteuid(getuid());
    set_name("算命先生", ({ "fortune teller", "teller" }));
    set_race("human");
    set_class("commoner");
    set_level(10);
    set("gender", "male");
    set("age", 60);
    set("long", @LONG
面容清癯，帶著一種看透世事的微笑，時不時捻著自己的八字鬍，邊整理桌面，邊等待想探知自身前程的人上門。
LONG
    );
    set_power("C");
    setup();
    carry_object("/obj/cloth")->wear();
}
