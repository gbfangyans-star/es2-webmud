// /d/lee/farm_w1.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "農家");
    set("long", @LONG
低矮農舍圍著小院，院裡擺著竹籃、農具與曬乾的作物。屋主人多半白日下田，只留下家人照看家務。
LONG
    );
    set("objects", ([
        "/d/lee/npc/woman" : 1
    ]));
    set("exits", ([
        "north" : __DIR__"wroad2"
    ]));
    setup();
    replace_program(ROOM);
}
