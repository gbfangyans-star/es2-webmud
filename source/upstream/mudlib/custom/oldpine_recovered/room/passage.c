inherit ROOM; void create(){ set("short","秘密通道入口"); set("long",@LONG
你现在正站在一个岩石的通道之中，在你南边有一片亮晶晶的帘幕
(curtain)，从帘幕后面传来阵阵轰隆隆的水声，通道两边的石壁上安置
著许多铜铸的烛台，照亮了这个岩穴，往北似乎有亮光。
LONG
); set("detail",(["curtain":"这片帘幕似乎是用一种极薄的丝绸织成的，后面还传来阵阵水声。\n"])); set("exits",(["north":__DIR__"secrectpath1","south":__DIR__"waterfall"])); set("map/area","老松林"); set("map/layer","洞穴"); setup(); }
