/* CUSTOM OLD PINE MAP — topology supplied by user; prose follows Snow-area style. */
inherit ROOM;

void create()
{
    set("short", "小路");
    set("long", @LONG
小路走到一處較低的坡腳，四周松木比先前高大許多，枝葉交錯，把天光切成細碎斑影。泥地上留著幾道新舊不一的腳印，顯然並非無人往來。道路在前方轉向東北，沿著老松林外緣繼續伸展。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "northwest" : __DIR__"path03",
        "northeast" : __DIR__"path05",
    ]));
    setup();
}
