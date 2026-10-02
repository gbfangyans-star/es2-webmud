// /d/oldpine/forest_n2.c — 老松林（P6）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

void create()
{
    set("short", "樹林");
    set("long", @LONG
一片幽靜的松林，粗大的樹幹上爬滿了青苔，偶爾有幾隻野鳥在枝頭吱吱喳喳地叫著，又倏地飛走。林間沒有像樣的路，只有前人砍斷的枝條和繫在樹上的布條指引方向，布條早已褪色，在風中無力地飄動著。往東、往西都還是一眼望不到盡頭的樹林。
LONG
    );
    set("exits", ([
        "west" : __DIR__"forest_n1",
        "east" : __DIR__"forest_n3",
    ]));
    set("map/area", "老松林");
    setup();
    replace_program(ROOM);
}
