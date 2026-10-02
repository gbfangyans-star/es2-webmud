// /d/oldpine/gravel_road.c — 老松林（J14）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "碎石路");
    set("long", @LONG
一條鋪著碎石的小路，碎石大小不一，走起來喀啦作響，是彤雲寺的僧人一擔一擔挑來鋪成的。路旁立著一塊小石碑，刻著「彤雲寺由此往西」。這裡是老松林中少數有人整理的路，往西可以到彤雲寺，往南接上官道，往北的林子裡卻不時傳來粗野的喧鬧聲。
LONG
    );
    set("exits", ([
        "west" : __DIR__"temple_gate",
        "north" : __DIR__"hideout",
        "south" : __DIR__"highway",
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
