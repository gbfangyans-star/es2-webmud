#include <npc.h>

inherit F_FIGHTER;

void create()
{
    seteuid(getuid());
    set_name("素衣派弟子", ({ "white-taoist", "white taoist", "white", "taoist", "素衣派弟子" }));
    set_race("woochan");
    set_class("taoist");
    set_level(30);

    // Race initialization fills every attribute not specified here.
    set_attr("con", 30);
    set_attr("wis", 25);
    set_attr("spi", 30);
    set_stat_maximum("gin", 500);
    set_stat_maximum("kee", 600);
    set_stat_maximum("sen", 800);

    set_skill("taoism-freeze", 160);
    set_skill("spells", 160);
    map_skill("spells", "taoism-freeze");

    set("long", "這名素衣派弟子精通天師道法【冰咒】，手持長劍，身穿布衣。\n");
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