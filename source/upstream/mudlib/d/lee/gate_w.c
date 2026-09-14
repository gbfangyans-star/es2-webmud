// /d/lee/gate_w.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "村口大門");
    set("long", @LONG
李家村西面的木製大門橫跨道路，門外道路通向村外，門內則接上筆直石子路。守衛偶爾在門旁巡看來往行人。
LONG
    );
    set("objects", ([
        "/d/lee/npc/guard" : 1
    ]));
    set("exits", ([
        "east" : __DIR__"wroad1"
    ]));
    setup();
    replace_program(ROOM);
}
