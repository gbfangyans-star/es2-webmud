// /d/wutang/npc/lee_shan.c — 五堂鎮 NPC：李山（依五堂鎮設計表）。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    seteuid(getuid());
    set_name("李山", ({ "lee shan", "lee", "shan" }));
    set_race("human");
    set_class("commoner");
    set_level(5);
    set("age", 25);
    set("long", @LONG
附近遊手好閒的小混混，時不時就會做出些令人苦惱的爛事。
LONG
    );
    set_skill("unarmed", 10);
    set_skill("dodge", 10);
    set_skill("parry", 10);
    // 約 5～7 tick 說一句（每 tick 16% 機率）。
    set("chat_chance", 15);
    set("chat_msg", ({
        "李山蹲在牆角，賊頭賊腦地東張西望，好像在提防著什麼人。\n",
        "李山不耐煩地踢了踢地上的石子：「看什麼看？沒見過人在這裡乘涼嗎？」\n",
    }));
    setup();
    set_stat_maximum("gin", 60);
    set_stat_effective("gin", 60);
    set_stat_current("gin", 60);
    set_stat_maximum("kee", 75);
    set_stat_effective("kee", 75);
    set_stat_current("kee", 75);
    set_stat_maximum("sen", 35);
    set_stat_effective("sen", 35);
    set_stat_current("sen", 35);
}
