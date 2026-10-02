// /d/oldpine/inn.c — 迷霧森林（R14）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit INN;

void init()
{
    ::init();
    add_action("do_enter", "enter");
}

int do_enter(string arg)
{
    object me = this_player();

    if( me->is_busy() || me->is_fighting() )
        return notify_fail("你現在沒有辦法這麼做。\n");
    message_vision("$N掀開布簾，走進了後頭的廚房。\n", me);
    if( !me->move("/d/oldpine/kitchen") ) return 0;
    message("vision", replace_string("$N從前頭的店裡走了進來。", "$N", me->name()) + "\n", environment(me), me);
    return 1;
}

void create()
{
    set("short", "野店");
    set("long", @LONG
迷霧森林裡一間用原木搭成的野店，屋簷下掛著一串串獸皮與風乾的鹿腿，門口豎著一根竹竿，挑著寫有「酒」字的布幌子。野店來往的人雖然不多，但獵戶和採藥人經常在此落腳，生意倒也還過得去；偶爾有獵人把打到的獵物賣給野店，烤肉的香味還吸引了附近的老饕前來光顧。往東可以回到林間空地，後頭（enter）是廚房。
LONG
    );
    set("exits", ([
        "east" : __DIR__"glade",
    ]));
    set("objects", ([
        __DIR__"npc/waiter" : 1,
    ]));
    set("map/area", "迷霧森林");
    setup();
}
