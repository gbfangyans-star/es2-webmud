// /d/oldpine/main_hall.c — 老松林（F12）。房間敘述照設計表原文。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "大雄寶殿");
    set("long", @LONG
這裡是彤雲寺的大雄寶殿﹐正殿供奉的是一尊巨大的大日如來神像﹐各式法器均整齊地放在一旁﹐神像前放著幾個蒲團﹐大殿的入口在你的南邊﹐東西兩邊各有一扇門通往寺院內部。
LONG
    );
    set("exits", ([
        "west" : __DIR__"side_hall_w",
        "east" : __DIR__"side_hall_e",
        "south" : __DIR__"temple_square",
    ]));
    set("objects", ([
        __DIR__"npc/da_guan" : 1,
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
