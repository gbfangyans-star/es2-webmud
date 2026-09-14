/* CUSTOM OLD PINE MAP — topology supplied by user; prose follows Snow-area style. */
inherit ROOM;

void create()
{
    set("short", "小路");
    set("long", @LONG
小路在老松之間斜向東北，地勢漸漸平緩。林木雖密，路中央卻被踩得十分清楚，顯然是通往林中某處的固定道路。東方隱約透出較明亮的天色，風聲裡偶爾夾著金鐵輕碰般的細響，轉瞬又被松濤掩去。
LONG
    );
    set("outdoors", "snow");
    set("exits", ([
        "southwest" : __DIR__"path06",
        "east" : __DIR__"path08",
    ]));
    setup();
}
