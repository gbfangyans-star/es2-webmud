// /d/oldpine/path2.c — 老松林（J10）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "林間小路");
    set("long", @LONG
林間的小路在這裡轉了個彎，路旁一棵老松的根部盤結隆起，被往來的人當成了歇腳的石凳，坐得光滑發亮。樹枝上掛著幾串風乾的野果，不知是哪個好心的旅人留下來給後人充飢的。近來路上行人稀少，樹根旁已經積了一層沒人掃的落葉。小路往西北通向林子深處，往東則能走到一塊空地。
LONG
    );
    set("exits", ([
        "northwest" : __DIR__"path1",
        "east" : __DIR__"crossing",
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
