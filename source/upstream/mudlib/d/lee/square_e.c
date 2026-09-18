// /d/lee/square_e.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "廣場");
    set("long", @LONG
廣場向東西兩側伸展，附近商販和村民常在此碰面交換消息。往南可到廣場中央，往北可回村北道路。地面鋪著大小不一的石板，縫隙間長著幾叢野草，倒也不影響往來行走。
LONG
    );
    set("exits", ([
        "west" : __DIR__"square_w",
        "east" : __DIR__"eroad1",
        "south" : __DIR__"square_c"
    ]));
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
