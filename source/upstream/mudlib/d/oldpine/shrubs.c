// /d/oldpine/shrubs.c — 迷霧森林（T16）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "矮樹叢");
    set("long", @LONG
一片低矮的灌木叢，枝葉間結滿了紅色的小漿果，酸甜的氣味混在霧氣裡。灌木叢中被人砍出了一條小路，路旁的樹枝上綁著一條褪色的紅布，大概是給迷路的人做的記號。霧中不時傳來幾聲粗魯的吆喝和大笑，聽起來不像是善類。往北可以回到林間空地，往西南是一片空地。
LONG
    );
    set("exits", ([
        "north" : __DIR__"glade",
        "southwest" : __DIR__"bandit_clearing",
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
