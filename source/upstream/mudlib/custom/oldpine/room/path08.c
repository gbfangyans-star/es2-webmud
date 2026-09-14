/* CUSTOM OLD PINE MAP — topology supplied by user; prose follows Snow-area style. */
inherit ROOM;

void create()
{
    set("short", "小路");
    set("long", @LONG
這裡的小路由西向東橫過老松林，兩側樹影沉沉，只有路中央留著一帶較亮的天光。泥地被反覆踏實，散落的枯枝多半被踢到路邊。向東望去還有數段小路相連，似乎有人刻意選了這處偏僻林地長住。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "west" : __DIR__"path07",
        "east" : __DIR__"path09",
        "north" : "/custom/oldpine_recovered/room/npath1",
    ]));
    setup();
}
