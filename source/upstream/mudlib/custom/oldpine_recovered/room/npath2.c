/* RECOVERED ES2 OLD PINE: mudchina/es2 d/oldpine/npath2.c. Path-only port. */
inherit ROOM;
void create(){
set("short", "林间小路");
set("long", @LONG
你现在正走在一条林间的小路上，小路两旁长满了高耸的松树，从
林间传来阵阵鸟叫声，小路往南北两个方向延伸出去。
LONG
);
set("exits", ([ "southeast": __DIR__"npath3", "north": __DIR__"npath1" ]));
set("outdoors", "oldpine"); set("map/area", "老松林"); set("map/layer", "地面");
setup();
}
