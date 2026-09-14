inherit ROOM; void create(){ set("short","小石桥"); set("long",@LONG
你现在正站在一座长满青苔的古桥上，桥下是一条山涧，几股清泉
在乱石之中向山下奔流，桥北边不远处有一个瀑布(waterfall)，从山
壁上犹如一条白练般垂了下来，瀑布两旁的石壁十分陡峭，桥边乱石间还垂著一根粗长的藤蔓(vine)，一路沿湿滑石壁伸向山涧下方。
LONG
); set("detail",(["vine":"其中有一根藤蔓距离你比较近，可以试著抓住(hold)藤蔓。\n"])); set("exits",(["west":__DIR__"epath1","east":__DIR__"epath3"])); set("outdoors","oldpine"); set("map/area","老松林"); set("map/layer","地面"); setup(); }
void init(){ add_action("do_hold_vine",({"hold","grab"})); }
int do_hold_vine(string arg){ if(!arg||arg!="vine") return notify_fail("你要抓住什么？\n"); message_vision("$N爬上石桥的护栏，伸手往不远处的一根藤蔓抓去....\n",this_player()); if(random((int)this_player()->query_skill("dodge"))<5){ message_vision("\n只听见一声惨叫，$N已经往山涧中坠了下去。\n\n",this_player()); this_player()->move(__DIR__"waterfall"); } else { message_vision("$N手脚俐落地攀附著藤蔓，慢慢地爬下山涧....。\n",this_player()); this_player()->move(__DIR__"passage"); } return 1; }
