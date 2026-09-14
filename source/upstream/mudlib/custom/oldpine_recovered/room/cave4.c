inherit ROOM;
void create(){
 set("short","山洞");
 set("long",@LONG
你现在已经到达山洞的深处了，四面八方都是些黑漆漆的小石洞，
简直不知道该往那里走，要不是还有一点光线，你都要彻底绝望了。
LONG
 );
 set("map/area","老松林"); set("map/layer","洞穴"); set("map/mode","maze");
 setup();
}
void reset(){
 ::reset();
 set("exits",([
  "south" : __DIR__"cave" + (random(4)+1),
  "north" : __DIR__"cave" + (random(4)+1),
  "west" : __DIR__"cave5",
  "east" : __DIR__"cave" + (random(4)+1),
 ]));
}
