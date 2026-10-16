// /d/qiaoyin/alchemy_room.c — 喬陰縣（P6）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "煉丹房");
    set("long", @LONG
這裡是方士煉丹的房間，裡面有許多的丹爐跟丹鼎，還有許多的松柴，由於煉丹需要專心，為了避免在煉丹時受到別人的打擾，這個房間有高級方士施以法術，專供方士專心煉丹用。
LONG
    );
    set("exits", ([
        "south" : __DIR__"big_hall",
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
