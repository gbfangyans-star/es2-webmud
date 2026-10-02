// /d/oldpine/mist3.c — 迷霧森林（R12）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "迷霧森林");
    set("long", @LONG
這裡的樹木長得歪歪斜斜，樹根像一條條巨蛇般隆出地面，一不留神就會被絆倒。霧氣中隱約傳來潺潺的水聲，循聲望去卻什麼也看不見。樹幹上被人用刀刻了幾個箭頭，指向東南方，大概是往來的獵戶留下的記號。往北可以回到林中的歇腳處，往東南的霧氣稍微淡了一些。
LONG
    );
    set("exits", ([
        "north" : __DIR__"mist2",
        "southeast" : __DIR__"glade",
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
