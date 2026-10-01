// /d/wutang/north_street.c — 五堂鎮（N10）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "五堂鎮");
    set("long", @LONG
從鎮口往南走，街道兩旁的店鋪漸漸多了起來，挑擔的小販與趕路的行人來來往往，越往鎮中心越顯得熱鬧。西邊是陸家的和豐當鋪，往北可以走回鎮口，往南就是鎮上最熱鬧的交叉路口。
LONG
    );
    set("exits", ([
        "north" : __DIR__"entrance",
        "west" : __DIR__"pawnshop",
        "south" : __DIR__"crossroad",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
