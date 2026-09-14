// /d/lee/pawnshop.c
// 李家村復原版。CONFIRMED_MIXED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "李記當鋪");
    set("long", @LONG
店裡兼做貨物買賣與典當生意，櫃臺後堆著標記不同的木箱。掌櫃李嘯天替李家打理此處產業，店門朝東開向街道。
LONG
    );
    set("objects", ([
        "/d/lee/npc/lee_xiao_tian" : 1,
        "/obj/food/mooncake" : 2
    ]));
    set("exits", ([
        "north" : __DIR__"square_s",
        "east" : __DIR__"street1"
    ]));
    setup();
    replace_program(ROOM);
}
