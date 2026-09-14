/* CUSTOM OLD PINE MAP — topology supplied by user; prose follows Snow-area style. */
inherit ROOM;

void create()
{
    set("short", "小路");
    set("long", @LONG
草棚已落在西北方身後，腳下的黃土路沿著鎮外緩坡向南蜿蜒。路旁野草被來往行旅踩得東倒西歪，稀疏松影從遠處斜落在路面上。風裡帶著乾燥松脂與泥土氣味，越往前走，雪亭鎮上的人聲便越顯微弱。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "northwest" : "/d/snow/sgate",
        "south" : __DIR__"path02",
    ]));
    setup();
}
