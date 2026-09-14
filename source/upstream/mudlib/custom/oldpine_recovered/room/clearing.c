/* RECOVERED ES2 OLD PINE: mudchina/es2 d/oldpine/clearing.c */
inherit ROOM;
void create(){
set("short","林间空地"); set("long",@LONG
这是一块林间空地，四周的树木花草像是被人修剪过一般，环绕著
空地围成一个整齐的圆形，空地中央一株巨大的松树(pine)像平地上撑
起一把大伞，树上针叶茂密得遮去了大半的阳光，空地四周有三条小路
分别通往东、西、南三个方向，往南的小路旁竖著一个牌子(sign)。
LONG
); set("detail",(["pine":"一株又高又大的松树，抬头似乎可见树梢有人影移动。\n","sign":"「官府告示：此处常有歹人出没。」\n"]));
set("exits",(["west":__DIR__"npath3","north":__DIR__"spath1","east":__DIR__"epath1"]));
set("outdoors","oldpine"); set("map/area","老松林"); set("map/layer","地面"); setup(); }
void init(){ add_action("do_climb","climb"); }
int do_climb(string arg){ if(arg!="pine") return 0; message_vision("$N手脚并用，敏捷地爬上了空地中央的大松树。\n",this_player()); this_player()->move(__DIR__"tree1"); return 1; }
