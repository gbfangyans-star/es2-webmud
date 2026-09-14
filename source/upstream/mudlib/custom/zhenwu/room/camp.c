/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "軍營");
    set("long", @LONG
這裡是振武軍營西側的營區入口，木柵與營帳沿路排列，來往軍士神色匆忙。東邊棚場後便是大片校場，遠處號令聲此起彼落；往東一路穿過營地，可回到雪亭鎮南方草棚附近。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "east" : __DIR__"shed",
    ]));
    setup();
}
