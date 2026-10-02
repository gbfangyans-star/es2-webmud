// /d/oldpine/wood4.c — 迷霧森林（T20）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "樹林");
    set("long", @LONG
這裡的樹木又高又密，枝葉交錯成一片厚實的頂篷，霧氣被困在林下，濃得幾乎可以用手撈起。地上的落葉積了不知多少年，踩下去鬆鬆軟軟，散發出一股潮濕的霉味。樹枝間不時有小動物竄過，抖落一串冰涼的水珠。往東北可以回去，往南是森林更深的地方。
LONG
    );
    set("exits", ([
        "northeast" : __DIR__"wood3",
        "south" : __DIR__"wood_deep",
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
