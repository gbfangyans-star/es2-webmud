// /d/lee/wroad2.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "石子路");
    set("long", @LONG
石子路穿過幾戶人家之間，北邊有獵戶住處，南邊則是農家院落。村民推著小車往來，路面十分平實。
LONG
    );
    set("exits", ([
        "west" : __DIR__"wroad1",
        "east" : __DIR__"wroad3",
        "north" : __DIR__"hunter",
        "south" : __DIR__"farm_w1"
    ]));
    setup();
    replace_program(ROOM);
}
