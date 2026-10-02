// /d/oldpine/path1.c — 老松林（H8）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "林間小路");
    set("long", @LONG
一條夾在松樹之間的泥土小路，路面被往來的人踩得結實，兩旁卻長滿了帶刺的荊棘，稍不留神就會勾破衣裳。路邊的泥地上留著幾個新鮮的馬蹄印，不遠處還有一小攤乾掉的血跡和一隻掉落的布鞋，讓人不禁加快了腳步。小路往西越走越窄，往東南則蜿蜒深入林中。
LONG
    );
    set("exits", ([
        "west" : __DIR__"path0",
        "southeast" : __DIR__"path2",
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
