// /d/wutang/npc/old_fire.c — 五堂鎮 NPC：老火（依五堂鎮設計表）。

#include <npc.h>
inherit F_VILLAGER;

void create()
{
    seteuid(getuid());
    set_name("老火", ({ "old fire", "lao huo" }));
    set_race("human");
    set_class("commoner");
    set_level(1);
    set("age", 55);
    set("long", @LONG
拉車多年的壯漢，雖然頗有年紀但依然勝任愉快。
LONG
    );
    set_skill("unarmed", 2);
    set_skill("dodge", 2);
    set_skill("parry", 2);
    // 約 5～7 tick 說一句（每 tick 16% 機率）。
    set("chat_chance", 15);
    set("chat_msg", ({
        "老火捶了捶腰，哈哈笑道：「拉了大半輩子的車，這兩條腿可還硬朗得很！」\n",
        "老火叼著煙桿，瞇眼望著北邊的大路：「這陣子往軍營去的人可真多啊。」\n",
    }));
    setup();
}
