// /d/lee/entrance_s.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "村口");
    set("long", @LONG
這裡是李家村南面的村口，北方木製大門後便是村內街道。往西南沿著小路離村，便可回到雪亭一帶兩條河流交會的河邊。
LONG
    );
    set("exits", ([
        "north" : __DIR__"gate_s",
        "southwest" : "/d/snow/egate"
    ]));
    setup();
    replace_program(ROOM);
}
