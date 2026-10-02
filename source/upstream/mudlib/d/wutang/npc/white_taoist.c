// /d/wutang/npc/white_taoist.c — 五堂鎮 NPC：白衣道士（依五堂鎮設計表）。

#include <npc.h>
inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("白衣道士", ({ "taoist", "white taoist" }));
    set_race("woochan");
    set_class("taoist");
    set_level(15);
    set("age", 25);
    set("long", @LONG
身上透出淡淡的寒氣，應該是修習冰咒的素衣派道士。
LONG
    );
    set_attr("spi", 28);
    set_attr("wis", 32);
    set_skill("taoism-freeze", 80);
    set_skill("spells", 120);
    map_skill("spells", "taoism-freeze");
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
    carry_object("/custom/armor/cloth/white_taoist_robe")->wear();
    carry_object("/obj/example/weapon/longsword")->wield();
}
