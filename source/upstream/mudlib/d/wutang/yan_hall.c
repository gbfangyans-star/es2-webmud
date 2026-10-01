// /d/wutang/yan_hall.c — 五堂鎮（V4）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "大廳");
    set("long", @LONG
顏家大宅的正廳，原本氣派的桌椅翻倒在地，名貴的瓷器碎了一地。幾具家僕與丫鬟的屍體橫陳在血泊之中，看來都是被一刀斃命。主人的座位空空蕩蕩，似乎在出事之前就已經逃走了。
LONG
    );
    set("exits", ([
        "out" : __DIR__"yan_mansion",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
