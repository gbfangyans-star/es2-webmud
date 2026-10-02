// /d/oldpine/wood2.c — 迷霧森林（V16）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "樹林");
    set("long", @LONG
林中的霧氣潮濕而清涼，樹下長著各式各樣的蕨類和野草，其中有不少是珍貴的藥材。地上被挖出了許多小坑，坑邊還留著新鮮的泥土，看來有採藥人剛在這裡忙碌過。遠處傳來一陣陣蘆葦被風吹動的沙沙聲，在霧中聽來格外清晰。往北和往南都有路可走。
LONG
    );
    set("exits", ([
        "north" : __DIR__"wood1",
        "south" : __DIR__"wood3",
    ]));
    set("objects", ([
        __DIR__"npc/herbalist" : 1,
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
