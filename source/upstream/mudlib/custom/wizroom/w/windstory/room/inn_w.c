#include <room.h>

inherit ROOM;
void create()
{
    set("short", "鄉校");
    set("long", @LONG這裡是雪亭鎮的鄉校，鎮民若對地方事務有所疑問，便會前來向校老申訴。廳內陳設簡樸，幾張木桌與長凳整齊排列，牆上貼著勸人向善的告示。西邊通往雪亭鎮廣場，東邊新設了一道厚重木門，門後便是供往來旅客歇腳的龍門客棧。
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
