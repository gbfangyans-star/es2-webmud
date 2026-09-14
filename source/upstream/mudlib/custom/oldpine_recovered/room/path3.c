inherit ROOM; void create(){ set("short","秘密通道"); set("long",@LONG
你现在正站在一个阴森森的山洞之中，一条昂首吐信的金银花蛇，
爬伏在一块突出的大青石(stone)上，令人望而生畏，也许你该回头逃跑了。
LONG
); set("detail",(["stone":"一块比人还高的钟乳石，虽然长满青苔，但爬(climb)上去应该不会太困难。\n"])); set("exits",(["south":__DIR__"secrectpath1"])); set("map/area","老松林"); set("map/layer","洞穴"); setup(); }
void init(){ add_action("do_climb","climb"); } int do_climb(string arg){ if(!arg||arg!="up") return notify_fail("只有向上(up)爬一条道。\n"); message_vision("$N慢慢地攀上大青石。\n",this_player()); this_player()->move(__DIR__"stone"); return 1; }
