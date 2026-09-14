/*
CUSTOM LEGACY-RESEARCH NPC PLACEMENT.
Identity/description grounded in user-authorized legacy ES2 research.
Apprenticeship and teacher skill table grounded in user-provided legacy teacher output.
Special-skill combat formulas remain intentionally unimplemented until source evidence is found.
*/
#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("高慎", ({ "kao shen", "kao", "shen"}));
    set_race("human");
    set("gender", "male");
    set_class("fighter");

    /* User-provided legacy teacher table: teaching ceilings. */
    set_skill("unarmed", 120);
    set_skill("parry", 120);
    set_skill("dodge", 120);
    set_skill("tiger-steps", 120);
    set_skill("sanmeendo", 140);
    set_skill("blade", 120);
    set_skill("twohanded blade", 120);
    set_skill("secondhand blade", 120);
    set_skill("force", 120);
    set_skill("tiger-force", 120);
    set_skill("tiger-blade", 140);
    set("long",
        "高慎是季縣虎刀門的耆宿，雖已年逾七旬，身形仍顯得十分硬朗。\n"
        "他眉目間帶著一股火爆剛烈之氣，站在老松林中也像一柄尚未入鞘的刀。\n"
        "據說他這次離開虎刀門，正是為了在外收幾名合意弟子，好讓門中後輩\n"
        "在一年一度的試會上爭一口氣。他看來膽識過人，一副天不怕地不怕的模樣。\n");
    set("chat_chance", 4);
    set("chat_msg", ({
        "高慎負手望著林間小路，冷哼一聲，神情頗為不耐。\n",
        "高慎伸手按了按腰間刀鞘，目光銳利地打量四周。\n",
    }));
    setup();
}

int accept_info(object ob, string type)
{
    return type == "skills";
}

/* No prerequisite: finding Gao Shen is enough to apprentice. */
int accept_apprentice(object me)
{
    if( me->query_class() != "fighter" ) {
        command("say 你連武者都不是, 不要想套近乎。");
        return 0;
    }

    if( me->query_skill("blade", 1) < 1 ) {
        command("say 你連刀都不會用, 回去多練幾招再來。");
        return 0;
    }

    return 1;
}

int init_apprentice(object me)
{
    if( ::init_apprentice(me) ) {
        me->set("title", "虎刀門弟子");
        me->set("custom_faction", "fighter.tiger");
        do_chat(({
            "高慎上下打量了你一番，忽然哈哈大笑道：好！既然敢拜，老夫便敢教！\n",
            "高慎沉聲說道：從今日起，你便是我虎刀門弟子。\n",
        }));
    }
    return 1;
}

/*
 * Acquisition gates from the user-provided legacy teacher output.
 * This only grants the skill seed. Combat formulas/actions for the three
 * tiger special skills are NOT invented here.
 */
int acquire_skill(object me, string skill)
{
    int cap;

    if( !me->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "unarmed": cap = 120; break;
    case "parry": cap = 120; break;
    case "dodge": cap = 120; break;
    case "tiger-steps": cap = 120; break;
    case "sanmeendo": cap = 140; break;
    case "blade": cap = 120; break;
    case "twohanded blade": cap = 120; break;
    case "secondhand blade": cap = 120; break;
    case "force":
        if( me->query_level() < 15 )
            return notify_fail("高慎搖頭道：你根基未穩，還是多練練吧。\n");
        cap = 120;
        break;
    case "tiger-force":
        if( me->query_level() < 15 )
            return notify_fail("高慎搖頭道：你根基未穩，還是多練練吧。\n");
        cap = 120;
        break;
    case "tiger-blade":
        if( me->query_skill("tiger-force", 1) < 30 )
            return notify_fail("高慎喝道：瘋虎功不到三十級，也敢妄學瘋虎刀法？\n");
        cap = 140;
        break;
    default:
        return 0;
    }

    if( me->query_skill(skill, 1) >= cap )
        return notify_fail("高慎說道：這門功夫老夫能教你的，已經到頂了。\n");

    if( !me->query_skill(skill, 1) ) {
        if( skill == "tiger-force" ) {
            /* User-provided rule: Tiger Force is completed directly at Lv20. */
            me->set_skill(skill, 20);
            /* The learned table is cumulative.  A skill granted directly at
             * Lv20 therefore starts at the Lv20 cumulative floor, otherwise
             * the first 20->21 step would incorrectly require the entire
             * Lv21 total from zero. */
            if( me->query_learn(skill) < 40000 ) me->set_learn(skill, 40000);
            if( !me->query("tiger_force/initial_con_bonus") ) {
                me->set_attr("con", me->query_attr("con", 1) + 1);
                me->set("tiger_force/initial_con_bonus", 1);
            }
            me->set("tiger_force/growth_level", 20);
            tell_object(me, "高慎將瘋虎功的入門心訣一氣傳下，你依法運轉數周天後豁然貫通，瘋虎功已練成二十級，根骨也隨之增長一點。\n");
            return 1;
        }
        me->set_skill(skill, 1);
        /* Common restored learned is cumulative: Lv1's floor is 100. */
        if( me->query_learn(skill) < 100 ) me->set_learn(skill, 100);
        tell_object(me, "高慎將「" + to_chinese(skill) + "」的入門要訣傳授給你。\n");
        return 1;
    }
    return 0;
}

int accept_fight()
{
    command("say 老夫今日是來收徒，不是陪你胡鬧的！");
    return 0;
}
