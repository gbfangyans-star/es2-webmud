/* CUSTOM ZHENWU CAMP MAP — topology and NPC placement supplied by user images. */
inherit ROOM;

void create()
{
    set("short", "校場");
    set("long", @LONG
校場西邊較為安靜，幾座兵器架在風中微微作響。地上散落著操練後留下的木屑，長槍與刀具劃過木樁的痕跡清晰可見，顯然每日都有不少新兵在此反覆磨練基本功。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "north" : __DIR__"yard04",
        "south" : __DIR__"yard10",
    ]));
    setup();
}
