// /d/lee/square_s.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "廣場");
    set("long", @LONG
這片廣場位在村中心偏南的位置，北面接著村中主路，東邊就是廣場中央。空地邊緣堆著幾捆備用的木料，像是村里修繕房舍時剩下的，平時倒也沒人特地搬動整理清掃。
LONG
    );
    set("exits", ([
        "north" : __DIR__"square_w",
        "east" : __DIR__"square_c"
    ]));
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
