// /d/oldpine/temple_gate.c — 老松林（H14）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "彤雲寺");
    set("long", @LONG
彤雲寺的山門，兩扇朱漆木門斑駁褪色，門楣上懸著一塊匾額，以蒼勁的筆法寫著「彤雲寺」三個大字。門前蹲著兩隻石獅，被風雨侵蝕得只剩下模糊的輪廓。聽說寺裡的住持到南方雲遊了好些年，香火一度冷清，最近才又熱鬧起來。往西進入寺內的廣場，往東是一條碎石路。
LONG
    );
    set("exits", ([
        "west" : __DIR__"temple_square",
        "east" : __DIR__"gravel_road",
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
