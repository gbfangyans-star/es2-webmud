// /d/wutang/npc/keeper.c — 五堂鎮 NPC：廟祝（依五堂鎮設計表）。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    seteuid(getuid());
    set_name("廟祝", ({ "keeper" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("age", 40);
    set("long", @LONG
鎮天神廟的廟祝，平日管理廟裡的大小事，最近正為了丟失廟裡的重要東西而發愁。
LONG
    );
    set_skill("unarmed", 2);
    set_skill("dodge", 2);
    set_skill("parry", 2);
    // 約 5～7 tick 說一句（每 tick 16% 機率）。
    set("chat_chance", 15);
    set("chat_msg", ({
        "廟祝望著神桌嘆了口氣：「那東西要是找不回來，我可怎麼向鎮天神交代啊……」\n",
        "廟祝拿著雞毛撢子撣了撣香爐，嘴裡唸唸有詞，不知道在祈求些什麼。\n",
    }));
    set_power("C");
    setup();
    carry_object("/obj/area/obj/cloth")->wear();
}
