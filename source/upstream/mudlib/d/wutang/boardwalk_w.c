// /d/wutang/boardwalk_w.c — 五堂鎮（J18）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "木道");
    set("long", @LONG
一條用木板鋪成的步道，架在濕軟的河灘上，踩上去會發出吱吱嘎嘎的聲響。兩旁長著高過人頭的蘆葦，風一吹便沙沙作響，偶爾還會驚起幾隻水鳥。往西是鯉君渡，往東可以走往三岔路口。
LONG
    );
    set("exits", ([
        "west" : __DIR__"ferry",
        "east" : __DIR__"boardwalk_e",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
