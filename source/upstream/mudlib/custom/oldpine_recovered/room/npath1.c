/* RECOVERED ES2 OLD PINE: mudchina/es2 d/oldpine/npath1.c. Path-only port; not yet connected. */
inherit ROOM;
void create(){
set("short", "林间小路");
set("long", @LONG
你现在正走在一条林间的小路，往北不远处走出这座林子就是雪亭
镇，小路两旁长满了许多高耸的松树，雪亭镇的居民都把这里叫做「老
松林」，据说林子里有株树龄上千的老松树，颇有灵验。
LONG
);
set("exits", ([ "south": __DIR__"npath2" ]));
set("outdoors", "oldpine");
set("map/area", "老松林"); set("map/layer", "地面");
setup();
}
