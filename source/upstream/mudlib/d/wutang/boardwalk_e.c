// /d/wutang/boardwalk_e.c — 五堂鎮（L18）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "木道");
    set("long", @LONG
木板步道的東段，木板已經有些老舊，縫隙間長出了青苔。往北是一片放牧著綿羊的草原，常能聽見羊群咩咩的叫聲，往東接到三岔路口，往西則通往鯉君渡，渡口那頭不時傳來船夫的吆喝聲。
LONG
    );
    set("exits", ([
        "west" : __DIR__"boardwalk_w",
        "east" : __DIR__"three_way",
        "north" : __DIR__"grass_se",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
