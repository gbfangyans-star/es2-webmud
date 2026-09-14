// /d/lee/watermelon_n3.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "西瓜田");
    set("long", @LONG
這片西瓜田已靠近村東溪流，田邊泥土較濕，偶爾能聽見溪水聲。田埂向西與其他瓜田相連。
LONG
    );
    set("exits", ([
        "west" : __DIR__"watermelon_n2",
        "south" : __DIR__"watermelon_s3",
        "northeast" : __DIR__"riverside_s"
    ]));
    setup();
    replace_program(ROOM);
}
