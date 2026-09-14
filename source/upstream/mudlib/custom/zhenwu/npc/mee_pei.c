#include <npc.h>
inherit F_SOLDIER;
void create(){ set_name("米沛", ({"mee-pei","mee pei","mee","米沛"})); set_race("human"); set_class("soldier"); set("gender","male"); set("nickname","振武軍提督"); set("long", "米沛是振武軍最高指揮官，身披戰甲，神情沉穩威嚴。他在軍中多年，以實戰與軍功一步步升任主將，看來約五十多歲。軍中傳聞具備相當實力的軍人可向他申請更進一步的職務，但相關條件目前仍待可靠資料補齊。\n"); setup(); }
int accept_fight(){ return 0; }
