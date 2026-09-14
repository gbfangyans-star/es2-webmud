// /d/lee/eroad2.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "石子路");
    set("long", @LONG
這段石子路鄰近村東，風中已帶著田野與溪水的氣味。向西可回廣場，向東則通往村口大門。
LONG
    );
    set("exits", ([
        "west" : __DIR__"eroad1",
        "east" : __DIR__"gate_e"
    ]));
    setup();
    replace_program(ROOM);
}
