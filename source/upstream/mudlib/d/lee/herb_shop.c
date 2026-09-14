// /d/lee/herb_shop.c
// 李家村復原版。CONFIRMED_MIXED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "藥鋪");
    set("long", @LONG
這是一間不大的藥鋪，木櫃裡分門別類收著藥材與丹藥，空氣中混著草根與藥香。掌櫃李岩守著櫃臺，店門朝東開向石子路。
LONG
    );
    set("objects", ([
        "/d/lee/npc/lee_yen" : 1
    ]));
    set("exits", ([
        "east" : __DIR__"nroad1"
    ]));
    setup();
    replace_program(ROOM);
}
