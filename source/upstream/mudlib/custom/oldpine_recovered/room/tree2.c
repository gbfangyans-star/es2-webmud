inherit ROOM; void create(){ set("short","大松树上"); set("long",@LONG
你现在正攀附在一株大松树的树干上，这里离地面已经有七、八丈
高，如果不小心跌了下去，不断条腿也得去半条命，松树上结了许多球
果，不过大部分都离树干很远，你构不到。
LONG
); set("exits",(["up":__DIR__"tree3","down":__DIR__"tree1"])); set("map/area","老松林"); set("map/layer","树上"); set("objects", ([ __DIR__"../npc/butterfly" : 6 ])); setup(); }
