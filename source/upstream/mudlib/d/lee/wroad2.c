// /d/lee/wroad2.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "石子路");
    set("long", @LONG
石子路穿過幾戶人家之間，北邊有獵戶住處，南邊則是農家院落。村民推著小車往來，路面十分平實。路旁堆著幾張晾曬的獸皮，散發著淡淡的皮革氣味，看得出這一帶住的多是靠山吃飯的人家。
LONG
    );
    set("exits", ([
        "west" : __DIR__"wroad1",
        "east" : __DIR__"wroad3",
        "north" : __DIR__"hunter",
        "south" : __DIR__"farm_w1"
    ]));
    create_door("south", "柴門", "north", DOOR_CLOSED);
    setup();
    replace_program(ROOM);
}
