// /d/wutang/npc/red_taoist.c — 五堂鎮 NPC：紅衣道士（依五堂鎮設計表）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("紅衣道士", ({ "taoist", "red taoist" }));
    set_race("human");
    set_class("taoist");
    set_level(15);
    set("age", 20);
    set("long", @LONG
一身道士打扮，看他的氣息應是朱衣派道士。
LONG
    );
    set_skill("taoism-fire", 80);
    set_skill("spells", 120);
    map_skill("spells", "taoism-fire");
    set("chat_chance_combat", 40);
    set("chat_msg_combat", ({
        (: command, "cast 1" :),
        (: command, "cast 2" :),
        (: command, "cast 3" :),
    }));
    setup();
    set_stat_maximum("gin", 180);
    set_stat_effective("gin", 180);
    set_stat_current("gin", 180);
    set_stat_maximum("kee", 195);
    set_stat_effective("kee", 195);
    set_stat_current("kee", 195);
    set_stat_maximum("sen", 300);
    set_stat_effective("sen", 300);
    set_stat_current("sen", 300);
    carry_object("/custom/armor/cloth/red_robe")->wear();
    carry_object("/obj/example/weapon/longsword")->wield();
}
