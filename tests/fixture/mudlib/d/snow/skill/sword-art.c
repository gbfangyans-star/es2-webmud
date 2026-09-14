inherit SKILL;
void create(){ DAEMON_D->register_skill_daemon("sword-art"); }
int valid_enable(string usage){ return usage=="sword" || usage=="parry"; }
void attack_using(object me, object op, object weapon){}
void parry_using(object me, object op, object weapon){}
