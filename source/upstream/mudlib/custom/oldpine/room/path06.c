/* CUSTOM OLD PINE MAP — topology supplied by user; prose follows Snow-area style. */
inherit ROOM;

void create()
{
    set("short", "小路");
    set("long", @LONG
這一段路筆直向北穿過兩片松林之間的狹窄空隙，厚厚松針覆住大半泥土，腳步聲也因此變得沉悶。幾株老松樹幹粗壯，樹皮龜裂如鱗，林間偶爾可見被人折斷的枝條，像是有人經常從這條路經過。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "south" : __DIR__"path05",
        "northeast" : __DIR__"path07",
    ]));
    setup();
}
