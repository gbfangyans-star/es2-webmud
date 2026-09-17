// /d/lee/grocery.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "雜貨鋪");
    set("long", @LONG
小小的雜貨鋪裡擺著油鹽、繩索、陶器與各式家常用品，貨架高低不一。這裡主要做附近村民的生意，東門通往石子路。櫃臺上擺著一把用得十分發亮的舊算盤，旁邊還堆疊著幾本記帳的簿冊，牆角還立著幾捆備用的麻繩與陶罐，看得出這裡的貨色雖不起眼，卻樣樣齊全。
LONG
    );
    set("objects", ([
        __DIR__"npc/lee_zhong" : 1
    ]));
    set("exits", ([
        "east" : __DIR__"nroad2"
    ]));
    setup();
    replace_program(ROOM);
}
