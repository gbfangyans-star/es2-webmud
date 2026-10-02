// /d/oldpine/glade.c — 迷霧森林（T14）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "林間空地");
    set("long", @LONG
迷霧森林中一塊難得開闊的空地，霧氣在這裡變得稀薄，抬頭還能望見一角灰濛濛的天空。空地西邊有一間冒著炊煙的野店，幾條小路從這裡向四方延伸，是林中往來的人必經之處。空地中央有一截被砍平的大樹樁，上面刻滿了旅人留下的名字。往西是野店，往北、西北、東、南都有路通往森林各處。
LONG
    );
    set("exits", ([
        "west" : __DIR__"inn",
        "north" : __DIR__"mist4",
        "northwest" : __DIR__"mist3",
        "east" : __DIR__"wood1",
        "south" : __DIR__"shrubs",
    ]));
    set("objects", ([
        __DIR__"npc/lin_yuchan" : 1,
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
