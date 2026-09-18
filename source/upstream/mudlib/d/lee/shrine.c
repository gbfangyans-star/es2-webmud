// /d/lee/shrine.c
// 李家村復原版。MODIFIED（原「福祠」改為聶晟的醫館，非原始 ES2 資料，由專案成員指定內容）
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "醫館");
    set("long", @LONG
這裡是聶晟看診行醫的醫館，四壁的木架上整齊排著大大小小的藥罐，靠窗的長案上攤著幾本醫書與銀針，
一旁垂著布簾，隔出裡間看診的地方。空氣中瀰著淡淡的藥草香。十多年前村裡爆發一場怪病，便是聶晟
在此治好了村民，李員外因此請他留下，成為村中的大夫。
LONG
    );
    set("exits", ([
        "south" : __DIR__"wroad3",
        "in" : __DIR__"nie_backroom"
    ]));
    set("objects", ([
        __DIR__"npc/nee_cheng" : 1,
        __DIR__"npc/herb_boy" : 2
    ]));
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
