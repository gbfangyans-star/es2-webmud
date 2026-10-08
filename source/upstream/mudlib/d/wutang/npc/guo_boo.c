// /d/wutang/npc/guo_boo.c — 五堂鎮 NPC：朱衣派道士 郭布（依五堂鎮設計表）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("郭布", ({ "guo boo", "guo", "boo" }));
    set_race("human");
    set_class("taoist");
    set_level(60);
    set("title", "朱衣派道士");
    set("age", 65);
    set("long", @LONG
一個神色剽悍的禿頭老者﹐若不是穿著道袍﹐說不定你會以為他是個武林豪傑。
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
    set_power("S");
    setup();
    carry_object("/custom/armor/cloth/red_robe")->wear();
    carry_object("/custom/armor/head/red_hat")->wear();
    carry_object("/custom/weapon/sword/sword_of_redrune")->wield();
}
