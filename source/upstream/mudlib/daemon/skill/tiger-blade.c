#include <ansi.h>
inherit SKILL;

mapping *actions = ({
(["action":"$N雙手猛提$w，腰背驟然發力，使出瘋虎刀法「猛虎出柙」，整個人挾著沉重刀勢撲向$n，刀鋒破風怒斬$n的$l。","attack":7,"force":7,"defense":-3,"damage_type":"割傷"]),
(["action":"$N一聲暴喝，雙手握緊$w使出「餓虎撲嶺」，腳下連踏數步逼近$n，刀勢自高處轟然壓落，帶著兇猛勁風劈向$n的$l。","attack":9,"force":8,"defense":-5,"damage_type":"割傷"]),
(["action":"$N沉腰旋身，雙手$w隨身勢橫掃，使出瘋虎刀法「虎尾橫江」，厚重刀光攔腰捲過，挾著狂猛力道掃向$n的$l。","attack":8,"force":9,"defense":-2,"damage_type":"割傷"]),
(["action":"$N猛踏地面，雙手持$w直闖$n中門，使出「怒虎穿林」，刀鋒在衝勢中由下翻上，狂烈勁道毫無保留地斬向$n的$l。","attack":11,"force":8,"defense":-6,"damage_type":"割傷"]),
(["action":"$N忽然收刀伏身，下一瞬雙手$w隨著轉腰之勢暴起，使出「伏虎翻身」，沉重刀鋒由極低處翻捲而上，猛襲$n的$l。","attack":6,"force":12,"defense":1,"damage_type":"割傷"]),
(["action":"$N仰首暴喝，雙手$w猛然高舉，使出瘋虎刀法「虎嘯裂谷」，全身力道隨刀鋒一併壓下，凜烈刀風直震$n的$l。","attack":10,"force":10,"defense":-7,"damage_type":"割傷"]),
});
private void create(){ seteuid(getuid()); DAEMON_D->register_skill_daemon("tiger-blade"); setup(); }
int valid_enable(string usage){ return usage=="twohanded blade"; }
private int strike(object me, object opponent, object weapon){ return COMBAT_D->fight(me,opponent,"tiger-blade",actions[random(sizeof(actions))],weapon); }
void attack_using(object me, object opponent, object weapon){
 int first_follow;
 if(!opponent) return;
 strike(me,opponent,weapon);
 /* 2010 tiger-blade update: skill >=90 and exert >70 guarantees first follow-up.
    Historical update explicitly removed the old ~75kg added force, so none is added here. */
 if(me->query_skill("tiger-blade",1)<90 || me->query("force_ratio")<=70) return;
 if(!living(opponent) || environment(me)!=environment(opponent)) return;
 message_vision(HIR "$N刀勢未盡，腳下一踏緊追而上，瘋虎刀法的追擊已如猛虎撲食般再次壓向$n！\n" NOR,me,opponent);
 first_follow = strike(me,opponent,weapon);
 /* First follow-up dealing damage triggers the second follow-up.
    rage is intentionally not invented here; when rage exists it can be added as the alternate trigger. */
 if(first_follow<=0 || !living(opponent) || environment(me)!=environment(opponent)) return;
 message_vision(HIR "$N見第一追已然得手，雙手長刀順勢再轉，第二追毫不停歇地直逼$n而去！\n" NOR,me,opponent);
 strike(me,opponent,weapon);
}
