inherit ROOM; void create(){ set("short","下坡道"); set("long",@LONG
这是一条笔直的坡道，北高南低，道路两旁长满了许多松树，从松
林间隐约可以听到东边传来流水的声音。
LONG
); set("exits",(["north":__DIR__"spath4","south":__DIR__"spath2"])); set("outdoors","oldpine"); set("map/area","老松林"); set("map/layer","地面"); setup(); }
