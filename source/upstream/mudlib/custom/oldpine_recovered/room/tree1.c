/* RECOVERED ES2 OLD PINE: spy intentionally isolated until black_cloth dependency is resolved. */
inherit ROOM; void create(){ set("short","大松树上"); set("long",@LONG
你现在正攀附在一株大松树的树干上，从这里可以很清楚地望见树
下的一切动静，而不被人发觉，似乎是个干偷鸡摸狗勾当的好地方。
LONG
); set("exits",(["up":__DIR__"tree2","down":__DIR__"clearing"])); set("map/area","老松林"); set("map/layer","树上"); setup(); }
