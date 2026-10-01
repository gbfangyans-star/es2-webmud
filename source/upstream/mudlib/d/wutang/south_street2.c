// /d/wutang/south_street2.c — 五堂鎮（N16）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "街道");
    set("long", @LONG
五堂鎮南邊的街道，兩旁的房舍漸漸稀疏，遠處可以望見一片綠油油的草原。路邊的大樹下有幾個老人坐著乘涼閒聊，旁邊拴著幾頭準備上路的驢子。往北走回到鎮上，往南不遠就是通往四方的三岔路口。
LONG
    );
    set("exits", ([
        "north" : __DIR__"south_street1",
        "south" : __DIR__"three_way",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
