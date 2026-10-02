// /d/oldpine/wood1.c — 迷霧森林（V14）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "樹林");
    set("long", @LONG
霧氣籠罩下的雜木林，樹幹上纏滿了藤蔓，藤上結著一串串紫黑色的果實，引來不少鳥雀啄食。地面上有幾道被重物拖過的痕跡，一路延伸到東北方的林子裡，痕跡旁還印著碗口大的爪印，看得人心頭一緊。往西可以回到空地，往東北和往南各有小路。
LONG
    );
    set("exits", ([
        "west" : __DIR__"glade",
        "northeast" : __DIR__"beast_trail",
        "south" : __DIR__"wood2",
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
