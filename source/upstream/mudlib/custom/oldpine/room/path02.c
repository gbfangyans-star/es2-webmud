/* CUSTOM OLD PINE MAP — topology supplied by user; prose follows Snow-area style. */
inherit ROOM;

void create()
{
    set("short", "小路");
    set("long", @LONG
這段小路夾在荒草與矮松之間，路面被車輪壓出兩道淺淺土痕。北方仍可望見草棚方向，東南方的樹木則逐漸密了起來。偶爾有枯枝在風中相互摩擦，發出細碎聲響，讓離鎮不遠的郊野已多了幾分寂靜。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "north" : __DIR__"path01",
        "southeast" : __DIR__"path03",
    ]));
    setup();
}
