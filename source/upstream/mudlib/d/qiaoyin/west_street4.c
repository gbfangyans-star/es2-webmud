// /d/qiaoyin/west_street4.c — 喬陰縣（J10）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "西大街");
    set("long", @LONG
西大街的東端，再往東就是城中心的樹王墳，遠遠就能望見那株齊腰而斷的大樹。這一帶的店家多半賣些香燭紙錢，據說是給前往樹王墳祭拜的人準備的，空氣中總帶著一股淡淡的檀香味。往西則是西大街。
LONG
    );
    set("exits", ([
        "west" : __DIR__"west_street3",
        "east" : __DIR__"tree_tomb",
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
