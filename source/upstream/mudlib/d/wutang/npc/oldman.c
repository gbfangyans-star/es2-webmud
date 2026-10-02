// /d/wutang/npc/oldman.c — 五堂鎮 NPC：老人（依五堂鎮設計表）。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    seteuid(getuid());
    set_name("老人", ({ "oldman", "old man", "man" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("age", 1200);
    set("long", @LONG
一位慈眉善目的老人，笑吟吟的看著你。
LONG
    );
    set_skill("unarmed", 2);
    set_skill("dodge", 2);
    set_skill("parry", 2);
    // 約 5～7 tick 說一句（每 tick 16% 機率）。
    set("chat_chance", 15);
    set("chat_msg", ({
        "老人坐在石椅上，瞇著眼睛曬太陽，看起來十分愜意。\n",
        "老人笑吟吟地說：「年輕人，常來這後院坐坐，對身子骨好啊。」\n",
    }));
    setup();
    carry_object("/obj/area/obj/cloth")->wear();
}
