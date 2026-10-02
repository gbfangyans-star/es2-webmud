// /d/oldpine/side_hall_w.c — 老松林（D12）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "側殿");
    set("long", @LONG
大雄寶殿西側的偏殿，殿內供奉著一尊手持淨瓶的觀音菩薩像，菩薩低眉垂目，神情慈悲。兩旁的木架上擺滿了經書，許多書頁已經泛黃，用細繩小心地綑紮著。供桌上點著一盞長明燈，微弱的火光映著牆上褪色的壁畫，畫的是菩薩救苦救難的故事。往東可以回到大雄寶殿。
LONG
    );
    set("exits", ([
        "east" : __DIR__"main_hall",
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
