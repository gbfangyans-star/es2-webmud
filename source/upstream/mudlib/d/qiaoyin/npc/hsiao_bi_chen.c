// /d/qiaoyin/npc/hsiao_bi_chen.c — 喬陰縣 NPC：蕭辟塵（依使用者設計表，2026-10-16）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("蕭辟塵", ({ "hsiao bi-chen", "hsiao", "bi-chen" }));
    set_race("human");
    set_class("fighter");
    set_level(5);
    set("gender", "male");
    set("age", 12);
    set("long", @LONG
外表看起來相當憔悴的小孩，但眼神堅毅異常，假以時日必定會有一番作為。
LONG
    );
    set_power("B");
    setup();
    carry_object("/obj/cloth")->wear();
}
