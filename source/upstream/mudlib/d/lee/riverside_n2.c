// /d/lee/riverside_n2.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "溪邊小路");
    set("long", @LONG
小路沿著溪岸南北延伸，腳下散布著細碎石子。溪水貼著村東流過，附近草木因水氣而顯得格外茂盛。
LONG
    );
    set("exits", ([
        "south" : __DIR__"riverside_n1"
    ]));
    setup();
    replace_program(ROOM);
}
