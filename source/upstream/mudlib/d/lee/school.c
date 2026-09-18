// /d/lee/school.c
// 李家村復原版。GENERATED
// Topology follows the user-provided Li Village map; generated prose is intentionally replaceable.

inherit ROOM;

void create()
{
    set("short", "私塾");
    set("long", @LONG
私塾裡整齊排著舊木桌椅，牆邊堆著幾冊翻得起毛的書本。白日常有孩童朗讀文章，窗外便是通往廣場的石子路。牆上掛著一幅「有教無類」的字幅，墨跡雖已略顯陳舊，仍看得出當年書寫時的用心。案頭擺著一方硯台與幾支毛筆，牆邊立著一根戒尺，看來平日規矩管教不算鬆散。
LONG
    );
    set("objects", ([
        "/d/lee/npc/lee_hsu_hsien" : 1,
        "/d/lee/npc/child" : 3
    ]));
    set("exits", ([
        "east" : __DIR__"nroad3"
    ]));
    setup();
    replace_program(ROOM);
    set("map/area", "李家村");
}
