// /d/qiaoyin/alley.c — 喬陰縣（R8）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "小巷子");
    set("long", @LONG
一條狹窄的小巷子，從東大街往北延伸過來，兩旁的高牆擋住了大半的陽光，青石板路面長著一層薄薄的青苔，走起來有些溼滑。巷子西邊有一間大屋，門口飄出淡淡的藥香與煙火味。往南可以回到東大街。
LONG
    );
    set("exits", ([
        "west" : __DIR__"big_hall",
        "south" : __DIR__"east_street3",
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
