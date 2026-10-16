// /d/qiaoyin/mid_lane2.c — 喬陰縣（H8）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "街道");
    set("long", @LONG
一條安靜的街道，兩旁是幾戶人家的後牆，牆頭探出幾枝桃花，在風中輕輕搖曳，落下的花瓣鋪了一地。偶爾有人家推開後門倒水，見到生人便又急忙關上。往北可以走到和豐當鋪門口，往南便接上西大街。
LONG
    );
    set("exits", ([
        "north" : __DIR__"mid_lane1",
        "south" : __DIR__"west_street3",
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
