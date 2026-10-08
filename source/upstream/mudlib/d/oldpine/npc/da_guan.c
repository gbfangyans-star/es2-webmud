// /d/oldpine/npc/da_guan.c — 老松林 NPC：彤雲寺住持 大觀和尚（依老松林設計表）。

#include <npc.h>

inherit F_FIGHTER;


void create()
{
    seteuid(getuid());
    set_name("大觀和尚", ({ "abbot da-gaun", "abbot", "da-gaun", "da gaun" }));
    set_race("human");
    set_class("monk");
    set_level(30);
    set("title", "彤雲寺住持");
    set("age", 60);
    set("long", @LONG
大觀和尚是彤雲寺的住持，到南方雲遊七年，幾天前才剛回來。
LONG
    );
    set_skill("twohanded staff", 120);
    set_skill("dodge", 40);
    set_skill("parry", 60);
    set_power("A");
    setup();
    carry_object("/custom/weapon/staff/wither_zenstaff")->wield();
    carry_object("/custom/armor/cloth/animitta_kasaya")->wear();
    carry_object("/custom/armor/neck/psakaml")->wear();
}
