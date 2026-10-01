// /d/wutang/school.c — 五堂鎮（J10）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "鄉校");
    set("long", @LONG
五堂鎮的鄉校，比一般的私塾大上許多，屋裡排滿了一張張書桌，學生們搖頭晃腦地唸著書。牆上貼著一張紅紙，寫著前幾年鎮上出了一位舉人，從那之後鎮民讀書的風氣便越來越盛。往南可以回到街道。
LONG
    );
    set("exits", ([
        "south" : __DIR__"west_street2",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
