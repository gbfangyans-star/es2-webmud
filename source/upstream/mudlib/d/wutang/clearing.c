// /d/wutang/clearing.c — 五堂鎮（H10）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "空地");
    set("long", @LONG
菜田前的一片空地，地上留著許多雜亂的蹄印，看來常有野豬從菜田那頭跑過來。空地邊緣擺著幾個用來嚇唬野豬的稻草人，可惜看來沒什麼用處。往西就是一大片菜田，往南則是通往五堂鎮的碎石路。
LONG
    );
    set("exits", ([
        "west" : __DIR__"field5",
        "south" : __DIR__"gravel_road_n",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
