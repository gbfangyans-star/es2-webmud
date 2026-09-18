// /d/lee/wroad3.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "石子路");
    set("long", @LONG
村西的石子路在這裡較寬，北側靠近醫館，南側仍是農家。向東再走便能抵達村中廣場。路面因為往來就診的村民較多，被踩得格外平整，偶爾能聞到醫館飄來的淡淡藥香，混著農家的泥土氣息。
LONG
    );
    set("exits", ([
        "west" : __DIR__"wroad2",
        "east" : __DIR__"wroad4",
        "north" : __DIR__"shrine",
        "south" : __DIR__"farm_w2"
    ]));
    create_door("south", "柴門", "north", DOOR_CLOSED);
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
