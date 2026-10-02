// /d/oldpine/path0.c — 老松林（F8）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "林間小路");
    set("long", @LONG
一段狹窄的林間小路，兩旁的老松枝椏低垂，行人得不時低頭，才不會被松枝刮到臉。路面上散落著被踩碎的松果，泥土裡還半埋著一隻斷了繩的草鞋和幾枚生鏽的銅錢，看來曾有人在這裡慌忙逃命。西北方隱約飄來柴火的煙味和粗野的笑罵聲，往東則接上一條較為平坦的小路。
LONG
    );
    set("exits", ([
        "northwest" : __DIR__"clearing_w",
        "east" : __DIR__"path1",
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
