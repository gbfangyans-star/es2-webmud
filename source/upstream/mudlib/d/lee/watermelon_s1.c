// /d/lee/watermelon_s1.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "西瓜田");
    set("long", @LONG
田裡瓜藤交錯，農人留下的腳印沿著窄窄田埂延伸。北面與另一片瓜田相連，西面靠近村中央街道。
LONG
    );
    set("exits", ([
        "west" : __DIR__"street1",
        "east" : __DIR__"watermelon_s2",
        "north" : __DIR__"watermelon_n1"
    ]));
    setup();
    replace_program(ROOM);
}
