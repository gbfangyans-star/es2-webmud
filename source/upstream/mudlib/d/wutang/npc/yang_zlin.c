// /d/wutang/npc/yang_zlin.c — 五堂鎮 NPC：冷梅莊一代弟子 楊子陵（依五堂鎮設計表）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("楊子陵", ({ "yang zlin", "yang", "zlin" }));
    set_race("human");
    set_class("fighter");
    set_level(45);
    set("title", "冷梅莊一代弟子");
    set("age", 30);
    set("long", @LONG
楊子陵在冷梅派第一代弟子中排行第四, 為梅影風某日出外於路上所遇到的棄嬰, 因機緣而入冷梅派, 目前劍術內功已略有小成, 一手真冷梅劍法在武林中也頗有微名。
LONG
    );
    set_attr("str", 35);
    set_attr("cor", 40);
    set_skill("unarmed", 90);
    set_skill("dodge", 90);
    set_skill("parry", 90);
    set_skill("sword", 90);
    // 約 5～7 tick 說一句（每 tick 16% 機率）。
    set("chat_chance", 15);
    set("chat_msg", ({
        "楊子陵負手而立，望著遠處的羿水，似乎在等什麼人。\n",
        "楊子陵輕撫劍柄，低聲道：「冷梅劍法講究的是一個『冷』字，心若不靜，劍便不冷。」\n",
    }));
    setup();
    set_stat_maximum("gin", 750);
    set_stat_effective("gin", 750);
    set_stat_current("gin", 750);
    set_stat_maximum("kee", 1300);
    set_stat_effective("kee", 1300);
    set_stat_current("kee", 1300);
    set_stat_maximum("sen", 150);
    set_stat_effective("sen", 150);
    set_stat_current("sen", 150);
    carry_object("/custom/weapon/sword/black_sword")->wield();
    carry_object("/custom/weapon/dagger/black_iron_dagger")->wield();
    carry_object("/custom/armor/cloth/silk_cloth")->wear();
    carry_object("/custom/armor/feet/wolf_boots")->wear();
    carry_object("/custom/armor/head/woof_hat")->wear();
}
