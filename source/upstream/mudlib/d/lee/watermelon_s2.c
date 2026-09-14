// /d/lee/watermelon_s2.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "西瓜田");
    set("long", @LONG
一畦畦西瓜向東西排列，部分瓜實已長得相當飽滿。田間沒有遮蔭，午後常能感到土地散出的熱氣。
LONG
    );
    set("exits", ([
        "west" : __DIR__"watermelon_s1",
        "east" : __DIR__"watermelon_s3",
        "north" : __DIR__"watermelon_n2"
    ]));
    setup();
    replace_program(ROOM);
}
