/* CUSTOM OLD PINE MAP — topology supplied by user; prose follows Snow-area style. */
inherit ROOM;

void create()
{
    set("short", "小路");
    set("long", @LONG
老松林中的道路在此變得平整，左右幾株古松枝幹橫伸，宛如天然門廊。路旁沒有店家與民舍，卻可見零星足跡與刀鞘拖過泥地留下的淺痕。再往東走，林間人跡反而更明顯，似乎前方有人停留。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "west" : __DIR__"path08",
        "east" : __DIR__"path10",
    ]));
    setup();
}
