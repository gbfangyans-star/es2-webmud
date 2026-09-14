inherit NPC;
void create(){ set_name("土匪喽罗",({"bandit"})); set("gender","男性"); set("age",33); set("long","这家伙满脸横肉，一副凶神恶煞的模样。\n"); set("combat_exp",3600); set("score",260); set("bellicosity",600); set("attitude","aggressive"); set_skill("sword",50); set_skill("parry",40); set_skill("dodge",40); setup(); carry_object(__DIR__"obj/short_sword")->wield(); add_money("silver",5); }
