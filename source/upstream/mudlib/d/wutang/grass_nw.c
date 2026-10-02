// /d/wutang/grass_nw.c — 五堂鎮（J14）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "草原");
    set("long", @LONG
一片青翠的草原，綠草長得又密又嫩，幾隻綿羊低著頭悠閒地吃著草，不時發出咩咩的叫聲。草原往東、往南延伸，遠處看得見五堂鎮的屋頂。草地上開著一些不知名的小黃花，偶爾有蝴蝶飛舞其間，十分恬靜。
LONG
    );
    set("exits", ([
        "east" : __DIR__"grass_ne",
        "south" : __DIR__"grass_sw",
    ]));
    set("objects", ([
        __DIR__"npc/sheep" : 2,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
