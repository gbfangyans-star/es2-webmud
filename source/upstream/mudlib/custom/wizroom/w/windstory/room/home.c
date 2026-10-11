#include <room.h>

inherit ROOM;
void create()
{
    set("short", "未知地方");
    set("long", @LONG這裡整個不見光，完全不知道有甚麼。
LONG
    );
    set("outdoors", __DIR__);
    set("exits", ([
        "east" : __DIR__"dragon_inn",
        "west" : "/d/snow/square_w",
    ]));
    create_door("east","客棧大門","west", DOOR_CLOSED);
    setup();
    replace_program(ROOM);
}
