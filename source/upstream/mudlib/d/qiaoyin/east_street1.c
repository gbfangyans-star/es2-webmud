// /d/qiaoyin/east_street1.c — 喬陰縣（N10）。依使用者設計表（2026-10-16）。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "東大街");
    set("long", @LONG
東大街的西端，鄰近城中心的樹王墳，街邊幾家茶館坐滿了閒聊的鄉民，說書人拍著醒木的聲音隔著窗子都聽得見，講到精彩處還會引來滿堂喝采。街口有個賣糖葫蘆的老漢，身邊總圍著幾個孩子。
LONG
    );
    set("exits", ([
        "west" : __DIR__"tree_tomb",
        "east" : __DIR__"east_street2",
    ]));
    set("map/area", "喬陰縣");
    setup();
    replace_program(ROOM);
}
