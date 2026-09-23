#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("米沛", ({"mee-pei", "mee pei", "mee", "pei", "米沛"}));
    set_race("human");
    set_class("soldier");
    set("gender", "male");
    set("nickname", "振武軍提督");

    set_attr("str", 40);
    set_attr("cor", 40);
    set_attr("con", 40);
    set_attr("cps", 35);
    set_attr("dex", 40);

    set_stat_maximum("gin", 600);
    set_stat_maximum("kee", 800);
    set_stat_maximum("sen", 200);

    set_skill("berserk", 180);
    set_skill("powerblow", 180);
    set_learn("powerblow", 1);
    set_skill("dodge", 120);
    set_skill("parry", 120);
    set_skill("unarmed", 150);
    set_skill("twohanded axe", 150);

    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: command, "berserk" :)
    }));

    set("long", "米沛是振武軍最高指揮官，身披戰甲，神情沉穩威嚴。他在軍中多年，以實戰與軍功一步步升任主將，看來約五十多歲。軍中傳聞具備相當實力的軍人可向他申請更進一步的職務，但相關條件目前仍待可靠資料補齊。\n");

    setup();

    carry_object("/custom/zhenwu/obj/steel_boots")->wear();
    carry_object("/custom/zhenwu/obj/fire_gauntlets")->wear();
    carry_object("/custom/zhenwu/obj/steel_armor")->wear();
    carry_object("/custom/zhenwu/obj/great_axe_of_mighty")->wield("twohanded axe");
}

int accept_fight()
{
    return 0;
}
