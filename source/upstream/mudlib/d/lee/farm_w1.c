// /d/lee/farm_w1.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "農家");
    set("long", @LONG
低矮農舍圍著小院，院裡擺著竹籃、農具與曬乾的作物。屋主人多半白日下田，只留下家人照看家務。院牆邊晾著幾件洗過的衣物，隨風輕輕擺動，屋簷下掛著一串串曬乾的辣椒與玉米，透出濃濃的農家氣息。院裡的婦人手裡忙著縫補衣物，見有人經過，總會抬頭善意地點個頭。
LONG
    );
    set("objects", ([
        "/d/lee/npc/woman" : 1
    ]));
    set("exits", ([
        "north" : __DIR__"wroad2",
        "east" : __DIR__"farm_w2"
    ]));
    create_door("north", "柴門", "south", DOOR_CLOSED);
    setup();
    replace_program(ROOM);
}
