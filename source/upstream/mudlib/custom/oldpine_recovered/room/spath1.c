/* bandit spawn held until recovered NPC set is staged. */
inherit ROOM; void create(){ set("short","林间小路"); set("long",@LONG
你现在正走在一片松树林中的小路上，小路往北通往一处空地，一
株巨大无朋的松树矗立在空地中央，小路往南是一条长长的下坡道，这
条路上足迹很多，显然常有人经过。
LONG
); set("exits",(["south":__DIR__"clearing","north":__DIR__"spath2"])); set("outdoors","oldpine"); set("map/area","老松林"); set("map/layer","地面"); setup(); }
