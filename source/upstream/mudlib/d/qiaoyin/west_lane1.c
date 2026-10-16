// /d/qiaoyin/west_lane1.c — 喬陰縣（D6）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "街道");
    set("long", @LONG
西門內的一條街道，路面鋪著青石板，兩旁是低矮的民宅，牆角長滿了青苔。這裡離城門不遠，常可以聽見守城官兵換班時的吆喝聲。往北便是西門，往南可以走到西大街。
LONG
    );
    set("exits", ([
        "north" : __DIR__"wgate",
        "south" : __DIR__"west_lane2",
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
