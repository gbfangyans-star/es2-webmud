// /d/wutang/grass_ne.c — 五堂鎮（L14）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "草原");
    set("long", @LONG
草原上微風徐徐，牧羊人倚著一根木杖看著羊群，偶爾吹起口哨把走遠的綿羊趕回來。往西、往南都還是一望無際的草地，草叢中不時竄出幾隻野兔，又飛快地鑽進草堆裡不見蹤影。
LONG
    );
    set("exits", ([
        "west" : __DIR__"grass_nw",
        "south" : __DIR__"grass_se",
    ]));
    set("objects", ([
        __DIR__"npc/sheep" : 2,
        __DIR__"npc/shepherd" : 1,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
