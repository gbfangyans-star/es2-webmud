// /d/oldpine/wood3.c — 迷霧森林（V18）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "樹林");
    set("long", @LONG
森林的南邊，霧氣在這裡被一片廣大的蘆葦叢擋住，樹林與蘆葦交界處長滿了濕漉漉的苔蘚。西邊的蘆葦叢一望無際，隨風起伏如海，據說曾有人走進去就再也沒有出來，附近的獵戶都繞道而行。往北可以回到林中，往西是蘆葦叢，往西南的樹林則越來越幽深。
LONG
    );
    set("exits", ([
        "north" : __DIR__"wood2",
        "west" : __DIR__"reeds",
        "southwest" : __DIR__"wood4",
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
