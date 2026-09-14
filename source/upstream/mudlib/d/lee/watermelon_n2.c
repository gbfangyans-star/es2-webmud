// /d/lee/watermelon_n2.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "西瓜田");
    set("long", @LONG
大片瓜藤沿田埂向東展開，葉下偶爾露出圓滾滾的西瓜。日照充足時，田間熱氣與泥土氣味格外明顯。
LONG
    );
    set("exits", ([
        "west" : __DIR__"watermelon_n1",
        "east" : __DIR__"watermelon_n3",
        "south" : __DIR__"watermelon_s2"
    ]));
    setup();
    replace_program(ROOM);
}
