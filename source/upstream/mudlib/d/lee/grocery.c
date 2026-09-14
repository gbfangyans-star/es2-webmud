// /d/lee/grocery.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "雜貨鋪");
    set("long", @LONG
小小的雜貨鋪裡擺著油鹽、繩索、陶器與各式家常用品，貨架高低不一。這裡主要做附近村民的生意，東門通往石子路。
LONG
    );
    set("exits", ([
        "east" : __DIR__"nroad2"
    ]));
    setup();
    replace_program(ROOM);
}
