#include <npc.h>
inherit F_SOLDIER;
void create(){ set_name("振武軍營士兵", ({"soldier","振武軍營士兵","士兵"})); set_race("human"); set_class("soldier"); set("long", "振武軍營士兵是天朝帝國邊防最基層的步兵。他身穿粗糙皮甲，手執沉重長槍，雖沒有江湖大俠般的絕頂輕功，卻有一身扎實的軍旅外家拳腳，每日都在營邊巡邏警戒。\n"); setup(); }
