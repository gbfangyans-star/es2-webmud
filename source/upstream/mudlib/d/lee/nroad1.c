// /d/lee/nroad1.c
// 李家村復原版。RECONSTRUCTED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "石子路");
    set("long", @LONG
平整石子鋪成的小路穿過村北，雨後石縫仍留著些水氣。西側是一間藥鋪，門前藥香隨風散出；南北兩端都是通往村中與村口的道路。路邊立著一根老石燈籠，每逢夜色降臨，便會有人點上燈火，替晚歸的村民照亮腳下的路。
LONG
    );
    set("exits", ([
        "north" : __DIR__"gate_n",
        "south" : __DIR__"nroad2",
        "west" : __DIR__"herb_shop"
    ]));
    setup();
    replace_program(ROOM);
}
