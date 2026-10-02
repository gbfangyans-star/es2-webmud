// /d/wutang/river_bank.c — 五堂鎮（J22）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "羿水河邊");
    set("long", @LONG
羿水河邊的一片沙灘，河水在這裡轉了個彎，流速緩了下來，水面上不時有魚兒躍出。岸邊散落著幾塊大石頭，是釣客們最喜歡的位置。往西北可以回到鯉君渡口。
LONG
    );
    set("exits", ([
        "northwest" : __DIR__"ferry_dock",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
