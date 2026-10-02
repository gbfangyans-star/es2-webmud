// /d/wutang/field3.c — 五堂鎮（F8）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "菜田");
    set("long", @LONG
菜田的東北角，這裡種的是一排排的豆藤，竹架子歪歪斜斜，有些已經被拱倒在地。泥地裡散落著被咬了一半的瓜果，引來了一群蒼蠅嗡嗡作響。往西、往南都還是菜田，幾隻野豬正埋頭在田裡大快朵頤。
LONG
    );
    set("exits", ([
        "west" : __DIR__"field2",
        "south" : __DIR__"field5",
    ]));
    set("objects", ([
        __DIR__"npc/boar" : 3,
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
