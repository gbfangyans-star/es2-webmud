// /d/wutang/npc/lu_estimator.c — 五堂鎮 NPC：陸四爺（依五堂鎮設計表）。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    seteuid(getuid());
    set_name("陸四爺", ({ "lu estimator", "lu", "estimator" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("age", 40);
    set("long", @LONG
陸家老四，做事圓融幹練，把家族的當舖生意照顧的有聲有色。
LONG
    );
    set_skill("unarmed", 2);
    set_skill("dodge", 2);
    set_skill("parry", 2);
    // 約 5～7 tick 說一句（每 tick 16% 機率）。
    set("chat_chance", 15);
    set("chat_msg", ({
        "陸四爺撥著算盤，頭也不抬地說：「客倌有什麼好東西，拿出來讓陸某估個價吧。」\n",
        "陸四爺端詳著手上的一枚古玉，嘖嘖稱奇：「好東西，好東西啊……」\n",
    }));
    set_power("C");
    setup();
}
