/* CUSTOM OLD PINE MAP — topology supplied by user; prose follows Snow-area style. */
inherit ROOM;

void create()
{
    set("short", "小路");
    set("long", @LONG
道路沿坡向東北爬升，左近是一片盤根錯節的老松，右側則散布著覆滿青苔的石塊。風吹過林梢時傳來低沉松濤，偶有鳥雀自枝間驚起。這裡已看不見雪亭鎮的屋瓦，只剩身後彎曲的小路還能指認來處。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "southwest" : __DIR__"path04",
        "north" : __DIR__"path06",
    ]));
    setup();
}
