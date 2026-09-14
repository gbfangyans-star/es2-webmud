inherit ROOM; void create(){ set("short","山涧之中"); set("long",@LONG
你现在正站在一条山涧中的岩石上，几股泉水正从你脚边流过，水
花溅得四处飞散，南边是一个深不见底的水潭(lake)，两边的山壁看起
来又高又陡，你的北方有一座小石桥高高地跨过两边的山壁。
LONG
); set("detail",(["lake":"南面的水潭幽深昏暗，水面映著两侧山壁，看不清潭底究竟有多深。\n","cliff":"两侧山壁陡峭，但岩面仍有些凹凸处可以攀附，看起来可以试著向上攀爬。\n"])); set("exits",(["north":__DIR__"riverbank2","south":__DIR__"lake"])); set("resource/water",1); set("outdoors","oldpine"); set("map/area","老松林"); set("map/layer","谷底"); setup(); }
/* cliff climb is intentionally held until cliff/pine escape chain is staged, preventing a recovery dead-end. */

void init(){ add_action("do_climb","climb"); }
int do_climb(string arg){ if(arg=="cliff"){ this_player()->move(__DIR__"cliff1"); return 1;} return notify_fail("你要爬什么？\n"); }
