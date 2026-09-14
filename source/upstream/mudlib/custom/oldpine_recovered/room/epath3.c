/* maniac isolated: necromancy dependency absent in current canonical source. */
inherit ROOM; void create(){ set("short","林间小路"); set("long",@LONG
你现在正走在一条松树林间的小路，西边有一座小石桥横跨在一条
山涧上，往东不远处似乎是林子的出口，一条破旧的栈道沿著山壁通往
山上，你发现地上有一些湿漉漉的脚印(footprints)，但是因为脚印太
多，分不出是往哪里去。
LONG
); set("detail",(["footprints":"一些杂乱的脚印散布在泥地上，其中不但有人留下的足迹，看起来还混著不少马蹄印。只是痕迹彼此交错，一时难以分辨究竟往哪个方向去了。\n"])); set("exits",(["west":__DIR__"epath2"])); set("outdoors","oldpine"); set("map/area","老松林"); set("map/layer","地面"); setup(); }
