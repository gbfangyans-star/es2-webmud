// /d/oldpine/mist_entrance.c — 迷霧森林（N10）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "森林入口");
    set("long", @LONG
老松林往東走到盡頭，樹木的種類漸漸變得雜亂，高大的樟樹與楓樹取代了松樹，林間開始飄起一層薄薄的白霧。路旁一棵大樟樹上刻著歪歪扭扭的幾個字：「霧深勿入」，旁邊還畫了個骷髏頭。這裡便是迷霧森林的入口，往西可以回到老松林，往東則是霧氣更濃的森林深處。
LONG
    );
    set("exits", ([
        "west" : __DIR__"crossing",
        "east" : __DIR__"mist1",
    ]));
    set("map/area", "迷霧森林");
    setup();
    replace_program(ROOM);
}
