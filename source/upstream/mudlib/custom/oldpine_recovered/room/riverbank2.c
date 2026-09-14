inherit ROOM; void create(){ set("short","山涧之中"); set("long",@LONG
你现在正站在一条山涧中的岩石上，一座小石桥正高高地从你的头
顶横跨过山涧两边的石壁(cliff)，一个瀑布就在你的北方不远处，从一
处更高的悬崖上垂了下来。
LONG
); set("detail",(["cliff":"小石桥下方的石壁陡峭湿滑，岩缝间长著青苔，顺著山涧向南延伸。\n"])); set("exits",(["north":__DIR__"waterfall","south":__DIR__"riverbank1"])); set("resource/water",1); set("outdoors","oldpine"); set("map/area","老松林"); set("map/layer","谷底"); setup(); }
