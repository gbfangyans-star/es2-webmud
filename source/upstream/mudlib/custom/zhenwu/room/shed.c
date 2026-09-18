/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "棚場");
    set("long", @LONG
一排簡陋木棚沿著軍營西側搭建，棚下堆著草束、木料與日常操演所需的雜物。地面有車輪與軍靴留下的痕跡，向東便是校場，向西則可通往軍營外側。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "east" : __DIR__"yard10",
        "west" : __DIR__"camp",
    ]));
    set("map/area", "振武軍營");
    setup();
}
