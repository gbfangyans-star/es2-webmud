// /d/qiaoyin/highway.c — 喬陰縣（B4）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "官道");
    set("long", @LONG
從五堂鎮通往喬陰縣的官道，路面被往來的車馬碾出兩道深深的車轍，兩旁是一畦畦的稻田，遠處已經可以望見喬陰縣城灰色的城牆。往西北可以回到五堂鎮外的三岔路口，往東不遠便是喬陰縣城的西門。
LONG
    );
    set("exits", ([
        "northwest" : "/d/wutang/three_way",
        "east" : __DIR__"wgate",
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
