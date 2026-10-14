// /d/wutang/npc/young_man.c — 五堂鎮 NPC：小鼠兒（依五堂鎮設計表）。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    seteuid(getuid());
    set_name("小鼠兒", ({ "young man", "xiao shu er" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("age", 15);
    set("long", @LONG
努力拉車的小伙子，經常往返兩地、服務鄉親。
LONG
    );
    set_skill("unarmed", 2);
    set_skill("dodge", 2);
    set_skill("parry", 2);
    // 約 5～7 tick 說一句（每 tick 16% 機率）。
    set("chat_chance", 15);
    set("chat_msg", ({
        "小鼠兒擦了擦額頭上的汗，拍拍車座：「客倌要上哪兒去？小的拉得又快又穩！」\n",
        "小鼠兒蹲在車旁啃著乾糧，眼睛還不時瞄向路口，深怕錯過了客人。\n",
    }));
    set_power("C");
    setup();
}
