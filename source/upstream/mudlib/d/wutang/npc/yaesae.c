// /d/wutang/npc/yaesae.c — 五堂鎮 NPC：玉面好漢 葉翔（依五堂鎮設計表）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("葉翔", ({ "yaesae", "ye xiang", "ye" }));
    set_race("human");
    set_class("thief");
    set_level(30);
    set("title", "玉面好漢");
    set("age", 30);
    set("long", @LONG
葉翔是武林中俠盜代表的佼佼者，時常劫富濟貧，是一個武林中豪
傑的代表，而他的容貌有如古代的潘安，所以被武林同道通稱為玉
面好漢，而他的輕功在武林中也是一絕。
LONG
    );
    set_attr("str", 20);
    set_attr("cor", 30);
    set_attr("dex", 35);
    set_attr("con", 28);
    set_skill("dodge", 110);
    set_skill("parry", 80);
    set_skill("dagger", 60);
    set_skill("unarmed", 100);
    set_skill("butterfly-steps", 110);
    // 約 5～7 tick 說一句（每 tick 16% 機率）。
    set("chat_chance", 15);
    set("chat_msg", ({
        "葉翔斜倚在公告欄旁，懶洋洋地打量著往來的富商，嘴角似笑非笑。\n",
        "葉翔低聲自語：「這鎮上有些人的銀子，也該拿出來分給窮苦人家了。」\n",
    }));
    setup();
    set_stat_maximum("gin", 360);
    set_stat_effective("gin", 360);
    set_stat_current("gin", 360);
    set_stat_maximum("kee", 450);
    set_stat_effective("kee", 450);
    set_stat_current("kee", 450);
    set_stat_maximum("sen", 150);
    set_stat_effective("sen", 150);
    set_stat_current("sen", 150);
}
