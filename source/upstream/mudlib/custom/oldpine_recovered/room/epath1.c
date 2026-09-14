inherit ROOM; void create(){ set("short","林间小路"); set("long",@LONG
你现在正走在一条松树林中的小路，这里的松树树干上都有著一些
奇怪的记号，像是被人用刀子划过，小路的西边是一块空地，往东不远
可以看到一条山涧，上面横跨著一座小石桥。
LONG
); set("exits",(["west":__DIR__"clearing","east":__DIR__"epath2"])); set("outdoors","oldpine"); set("map/area","老松林"); set("map/layer","地面"); setup(); }
