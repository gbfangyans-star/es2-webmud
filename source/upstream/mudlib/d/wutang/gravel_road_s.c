// /d/wutang/gravel_road_s.c — 五堂鎮（F14）。房間敘述依設計表需求擴寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "碎石路");
    set("long", @LONG
碎石路往西南延伸，路旁的雜草漸漸茂密起來，空氣中帶著河水的濕氣。遠處傳來潺潺的流水聲與船夫的吆喝聲，越往西走路面越是濕滑。往西走就是羿水河邊，往東北則可以走回五堂鎮的方向。
LONG
    );
    set("exits", ([
        "west" : __DIR__"riverside",
        "northeast" : __DIR__"gravel_road_n",
    ]));
    set("map/area", "五堂鎮");
    setup();
    replace_program(ROOM);
}
