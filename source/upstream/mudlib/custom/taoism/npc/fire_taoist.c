#include <npc.h>

inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("朱衣派弟子", ({ "red-taoist", "red taoist", "red", "taoist", "朱衣派弟子" }));
    set_race("avatar");
    set_class("taoist");
    set_level(30);

    // Race initialization fills every attribute not specified here.
    set_attr("con", 30);
    set_attr("wis", 25);
    set_attr("spi", 30);
    set_stat_maximum("gin", 500);
    set_stat_maximum("kee", 600);
    set_stat_maximum("sen", 800);

    set_skill("taoism-fire", 160);
    set_skill("spells", 160);
    map_skill("spells", "taoism-fire");

    set("long", "這名朱衣派弟子精通天師道法【火術】，手持長劍，身穿布衣。\n");
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: command, "cast 1" :),
        (: command, "cast 2" :),
        (: command, "cast 3" :),
        (: command, "cast 4" :)
    }));

    setup();
    carry_object("/obj/area/obj/cloth")->wear();
    carry_object("/obj/area/obj/longsword")->wield();
}