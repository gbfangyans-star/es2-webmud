// /d/lee/gate_e.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "村口大門");
    set("long", @LONG
李家村東面的村口大門立在道路盡頭，門外很快便接近溪畔。木門兩旁有簡單的守望位置，方便村民巡看。
LONG
    );
    set("objects", ([
        "/d/lee/npc/guard" : 1
    ]));
    set("exits", ([
        "west" : __DIR__"eroad2",
        "east" : __DIR__"riverside_s"
    ]));
    setup();
    replace_program(ROOM);
}
