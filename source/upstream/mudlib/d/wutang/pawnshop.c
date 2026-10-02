// /d/wutang/pawnshop.c — 五堂鎮（L10）。房間敘述照設計表原文。

#include <room.h>

inherit HOCKSHOP;

void create()
{
    set("short", "和豐當鋪");
    set("long", @LONG
這裡是一家中等規模的當鋪﹐老闆便是五堂鎮上陸姓一堂的當家﹐因為陸家的祖先是從經營當鋪發跡的﹐因此這家當鋪也被視為是陸家家長的主要基業﹐現在的大朝奉是由陸大當家的四弟擔任﹐大家都稱他陸四爺﹐當鋪的出口在東邊﹐北邊的牆上掛著一幅工筆花鳥﹐西邊是櫃臺﹐通往內間的門就在櫃臺邊﹐不過顯然是從裡面鎖著的。
LONG
    );
    set("exits", ([
        "east" : __DIR__"north_street",
    ]));
    set("objects", ([
        __DIR__"npc/lu_estimator" : 1,
    ]));
    set("no_fight", 1);
    set("map/area", "五堂鎮");
    setup();
}
