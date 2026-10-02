// /d/oldpine/reeds_exit.c — 迷霧森林（T18x）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "蘆葦叢");
    set("long", @LONG
蘆葦叢的邊緣，高大的蘆葦終於稀疏了下來，露出一小片乾燥的土丘。土丘上長著幾株罕見的草藥，在潮濕的霧氣中顯得格外青翠，看來很少有人能找到這裡。從土丘上望出去，東邊隱約可以看見樹林的輪廓，總算是找到了出路。往東可以離開蘆葦叢。
LONG
    );
    set("exits", ([
        "east" : __DIR__"wood3",
    ]));
    set("objects", ([
        __DIR__"npc/herbalist" : 1,
    ]));
    set("map/area", "迷霧森林");
    set("map/layer", "蘆葦叢邊緣");
    setup();
    replace_program(ROOM);
}
