// /d/oldpine/reeds.c — 迷霧森林（T18）。房間敘述依設計表提示撰寫。

#include <room.h>

inherit ROOM;

// 蘆葦叢的無限迴廊：畫面永遠顯示四個出口（都通回這裡），
// 依序走 north、north、east、west、north 才會到出口房；走錯一步進度歸零，
// 畫面和走對時一模一樣。剛進來（還沒走對任何一步）時往 east 可以回到樹林。
#define SEQ ({ "north", "north", "east", "west", "north" })
#define EXIT_ROOM "/d/oldpine/reeds_exit"
#define BACK_ROOM "/d/oldpine/wood3"

void init()
{
    ::init();
    // 剛從外面走進來，進度從頭算起。
    if( this_player() ) this_player()->delete_temp("oldpine_reeds");
    add_action("do_go", ({ "go", "north", "south", "east", "west" }));
}

int do_go(string arg)
{
    object me = this_player();
    string dir = query_verb() == "go" ? arg : query_verb();
    int step;

    if( member_array(dir, ({ "north", "south", "east", "west" })) < 0 ) return 0;
    if( me->is_busy() || me->over_encumbranced() ) return 0;

    step = me->query_temp("oldpine_reeds");
    if( !step && dir == "east" ) {
        me->delete_temp("oldpine_reeds");
        message("vision", me->name() + "撥開蘆葦往東離開。\n", this_object(), me);
        me->move(BACK_ROOM);
        message("vision", me->name() + "從西邊的蘆葦叢裡鑽了出來。\n", environment(me), me);
        return 1;
    }
    if( dir == SEQ[step] ) step++;
    else step = 0;

    message("vision", me->name() + "在蘆葦叢裡繞來繞去，一下子就不見了蹤影。\n", this_object(), me);
    if( step >= sizeof(SEQ) ) {
        me->delete_temp("oldpine_reeds");
        me->move(EXIT_ROOM);
        message("vision", me->name() + "從蘆葦叢裡鑽了出來。\n", environment(me), me);
        return 1;
    }
    me->set_temp("oldpine_reeds", step);
    write("你撥開蘆葦往前走了一段路 ...\n");
    me->command("look");
    return 1;
}

void create()
{
    set("short", "蘆葦叢");
    set("long", @LONG
一望無際的蘆葦叢，蘆葦長得比人還高，密密麻麻地擋住了視線，四面八方看起來都一模一樣。腳下是濕軟的泥地，每走一步都會陷下去半寸，身後的足跡很快又被泥水填平。風吹過蘆葦，發出沙沙的聲響，彷彿有人在耳邊低語，讓人完全分不清東南西北。
LONG
    );
    set("exits", ([
        "north" : __DIR__"reeds",
        "south" : __DIR__"reeds",
        "east" : __DIR__"reeds",
        "west" : __DIR__"reeds",
    ]));
    set("map/area", "迷霧森林");
    set("map/layer", "蘆葦叢");
    setup();
}
