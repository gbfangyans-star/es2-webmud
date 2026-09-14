inherit NPC;
void create(){ set_name("黑冠巨蟒",({"serpent","snake"})); set("race","蛇类"); set("age",20); set("combat_exp",250000); set("max_gin",900); set("gin",900); set("max_kee",1800); set("kee",1800); set("max_sen",900); set("sen",900); set("attitude","aggressive"); set_temp("apply/attack",60); set_temp("apply/armor",90); set_skill("dodge",80); setup(); }
