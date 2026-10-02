// /d/oldpine/npc/lin_yuchan.c — 迷霧森林 NPC：逆靈宮四宮主 靈玉嬋（依老松林設計表）。

#include <npc.h>

inherit F_FIGHTER;


void create()
{
    seteuid(getuid());
    set_name("靈玉嬋", ({ "lin yu-chan", "lin", "yu-chan" }));
    set_race("human");
    set_class("fighter");
    set_level(30);
    set("title", "逆靈宮四宮主");
    set("gender", "female");
    set("age", 18);
    set("long", @LONG
一位膚色白皙的女郎，眉頭深鎖，似乎正在為什麼事情煩心。
LONG
    );
    set_attr("str", 20);
    set_attr("cor", 20);
    set_attr("cps", 22);
    set_attr("dex", 22);
    set_attr("con", 20);
    set_skill("dodge", 100);
    set_skill("parry", 100);
    set_skill("unarmed", 80);
    set_skill("force", 60);
    setup();
    set_stat_maximum("gin", 180);
    set_stat_effective("gin", 180);
    set_stat_current("gin", 180);
    set_stat_maximum("kee", 200);
    set_stat_effective("kee", 200);
    set_stat_current("kee", 200);
    set_stat_maximum("sen", 120);
    set_stat_effective("sen", 120);
    set_stat_current("sen", 120);
    carry_object("/custom/armor/feet/violet_shoes")->wear();
    carry_object("/custom/armor/cloth/violet_cloth")->wear();
    carry_object("/custom/armor/head/violet_hairpin")->wear();
    carry_object("/custom/armor/waist/voliet_jade")->wear();
}
