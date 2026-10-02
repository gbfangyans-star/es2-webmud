// /d/oldpine/forest_n3.c — 老松林（R6）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "樹林");
    set("long", @LONG
這裡的松樹稍微稀疏了些，陽光從枝葉的縫隙灑下來，在地上投出斑駁的光影。東北方的林子後面不時傳來刀刃劈開空氣的呼呼聲；東南方的地勢漸漸低下去，長滿了半人高的雜草。往西則是更深的松林，林子裡靜得只剩下自己的腳步聲。
LONG
    );
    set("exits", ([
        "west" : __DIR__"forest_n2",
        "southeast" : __DIR__"grass1",
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
