// /d/oldpine/mist4.c — 迷霧森林（T12）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "迷霧森林");
    set("long", @LONG
一片長滿青草的林間窪地，霧氣在此聚積不散，像一池靜止的白水。草地上滿是蹄印和被啃食過的草根，四周的樹皮也被磨去了一塊塊，看來常有野鹿成群在此覓食。一有風吹草動，草叢深處便傳來一陣慌亂的蹄聲，接著又歸於平靜。往南可以走到一塊林間空地。
LONG
    );
    set("exits", ([
        "south" : __DIR__"glade",
    ]));
    set("objects", ([
        __DIR__"npc/deer" : 4,
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
