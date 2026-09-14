// /d/lee/gate_s.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "村口大門");
    set("long", @LONG
李家村南面的村口大門守著主要進村道路。從這裡往北就是村內街道，往南則通向村口與外面的道路。
LONG
    );
    set("exits", ([
        "north" : __DIR__"street2",
        "south" : __DIR__"entrance_s"
    ]));
    setup();
    replace_program(ROOM);
}
