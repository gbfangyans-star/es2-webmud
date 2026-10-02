// /d/oldpine/reeds3.c — 迷霧森林（T18）。蘆葦叢迷宮第 3 段（外觀與 reeds 相同）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "蘆葦叢");
    set("long", @LONG
一望無際的蘆葦叢，蘆葦長得比人還高，密密麻麻地擋住了視線，四面八方看起來都一模一樣。腳下是濕軟的泥地，每走一步都會陷下去半寸，身後的足跡很快又被泥水填平。風吹過蘆葦，發出沙沙的聲響，彷彿有人在耳邊低語，讓人完全分不清東南西北。
LONG
    );
    set("exits", ([
        "north" : __DIR__"reeds",
        "south" : __DIR__"reeds",
        "east" : __DIR__"reeds4",
        "west" : __DIR__"reeds",
    ]));
    set("map/area", "迷霧森林");
    set("map/layer", "蘆葦叢");
    setup();
    replace_program(ROOM);
}
