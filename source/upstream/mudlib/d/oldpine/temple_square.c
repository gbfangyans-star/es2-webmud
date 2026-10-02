// /d/oldpine/temple_square.c — 老松林（F14）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "彤雲寺");
    set("long", @LONG
彤雲寺大殿前的廣場，地上鋪著平整的青石板，石縫裡長出幾叢青草。廣場中央立著一座三足銅香爐，爐中插滿了香，裊裊青煙飄向北邊莊嚴的大雄寶殿。廣場兩側種著幾棵老松，樹下擺著石凳，偶爾有僧人拿著竹掃帚在此清掃落葉。往北是大雄寶殿，往東可以走出寺門。
LONG
    );
    set("exits", ([
        "north" : __DIR__"main_hall",
        "east" : __DIR__"temple_gate",
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
