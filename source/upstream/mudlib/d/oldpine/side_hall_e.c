// /d/oldpine/side_hall_e.c — 老松林（H12）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "側殿");
    set("long", @LONG
大雄寶殿東側的偏殿，殿內供奉著十八羅漢的泥塑像，有的怒目圓睜，有的含笑撫膝，個個神態不同、栩栩如生。殿角放著一面大鼓和一口銅鐘，鐘身刻滿了經文，看得出年代久遠。地上的青磚被跪拜的人磨得光亮，蒲團上還留著淺淺的膝印。往西可以回到大雄寶殿。
LONG
    );
    set("exits", ([
        "west" : __DIR__"main_hall",
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
